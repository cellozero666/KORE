use std::sync::Arc;
use std::time::{SystemTime, UNIX_EPOCH};
use tokio::sync::Mutex as TokioMutex;

use log::{info, warn};
use tauri::Manager;
use tauri_plugin_opener::OpenerExt;
use urlencoding::encode;

use crate::communication::protocol::format_command;
use crate::config::{GOOGLE_CLIENT_ID, GOOGLE_CLIENT_SECRET, GOOGLE_REDIRECT_URI};
use crate::events::google;
use crate::models::google::{
    CalendarListResponse, GmailListResponse, GmailMessageResponse,
    GoogleProfile, GoogleStatus, GoogleTokenResponse, GoogleUser,
};
use crate::state::connection::AppState;
use crate::state::google::GoogleState;

const GOOGLE_ACCOUNTS_BASE: &str = "https://accounts.google.com";
const GOOGLE_OAUTH2_BASE: &str = "https://www.googleapis.com/oauth2/v2";
const GMAIL_BASE: &str = "https://gmail.googleapis.com/gmail/v1";
const CALENDAR_BASE: &str = "https://www.googleapis.com/calendar/v3";
const SCOPES: &str = "openid profile email https://www.googleapis.com/auth/gmail.readonly https://www.googleapis.com/auth/calendar.readonly";

// ─── PKCE ─────────────────────────────────────────────────────────────────────

fn generate_pkce() -> (String, String) {
    use rand::RngCore;
    let mut verifier = vec![0u8; 64];
    rand::rngs::OsRng.fill_bytes(&mut verifier);
    let code_verifier = base64_url_encode(&verifier);
    let challenge = sha256_hash(&code_verifier);
    (code_verifier, challenge)
}

fn base64_url_encode(data: &[u8]) -> String {
    use base64::Engine;
    base64::engine::general_purpose::URL_SAFE_NO_PAD.encode(data)
}

fn sha256_hash(input: &str) -> String {
    use sha2::Digest;
    let mut hasher = sha2::Sha256::new();
    hasher.update(input.as_bytes());
    let result = hasher.finalize();
    base64_url_encode(&result)
}

// ─── OAuth helpers ────────────────────────────────────────────────────────────

async fn exchange_code(code: &str, code_verifier: &str) -> Result<GoogleTokenResponse, String> {
    let client = reqwest::Client::new();
    let params = [
        ("grant_type", "authorization_code"),
        ("code", code),
        ("redirect_uri", GOOGLE_REDIRECT_URI),
        ("client_id", GOOGLE_CLIENT_ID),
        ("client_secret", GOOGLE_CLIENT_SECRET),
        ("code_verifier", code_verifier),
    ];

    let resp = client
        .post(format!("{}/o/oauth2/token", GOOGLE_ACCOUNTS_BASE))
        .form(&params)
        .send()
        .await
        .map_err(|e| format!("token exchange request failed: {}", e))?;

    if !resp.status().is_success() {
        let status = resp.status();
        let body = resp.text().await.unwrap_or_default();
        return Err(format!("token exchange failed ({}): {}", status, body));
    }

    resp.json::<GoogleTokenResponse>()
        .await
        .map_err(|e| format!("token exchange parse failed: {}", e))
}

async fn refresh_access_token(refresh_token: &str) -> Result<GoogleTokenResponse, String> {
    let client = reqwest::Client::new();
    let params = [
        ("grant_type", "refresh_token"),
        ("refresh_token", refresh_token),
        ("client_id", GOOGLE_CLIENT_ID),
        ("client_secret", GOOGLE_CLIENT_SECRET),
    ];

    let resp = client
        .post(format!("{}/o/oauth2/token", GOOGLE_ACCOUNTS_BASE))
        .form(&params)
        .send()
        .await
        .map_err(|e| format!("token refresh request failed: {}", e))?;

    if !resp.status().is_success() {
        let status = resp.status();
        let body = resp.text().await.unwrap_or_default();
        return Err(format!("token refresh failed ({}): {}", status, body));
    }

    let mut token: GoogleTokenResponse = resp
        .json()
        .await
        .map_err(|e| format!("token refresh parse failed: {}", e))?;

    if token.refresh_token.is_none() {
        token.refresh_token = Some(refresh_token.to_string());
    }

    Ok(token)
}

async fn ensure_token(google_state: &GoogleState) -> Result<String, String> {
    let mut inner = google_state.inner.lock().await;

    let now = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_secs();

    if let Some(ref token) = inner.access_token {
        if now < inner.expires_at {
            return Ok(token.clone());
        }
    }

    let refresh_token = inner
        .refresh_token
        .clone()
        .ok_or_else(|| "no refresh token available".to_string())?;

    let token_response = refresh_access_token(&refresh_token).await?;

    inner.access_token = Some(token_response.access_token.clone());
    inner.expires_at = now + token_response.expires_in;

    if let Some(new_refresh) = &token_response.refresh_token {
        if new_refresh != &refresh_token {
            inner.refresh_token = Some(new_refresh.clone());
        }
    }

    Ok(token_response.access_token)
}

// ─── API calls ────────────────────────────────────────────────────────────────

async fn fetch_user_profile(google_state: &GoogleState) -> Result<GoogleUser, String> {
    let token = ensure_token(google_state).await?;
    let client = reqwest::Client::new();

    let resp = client
        .get(format!("{}/userinfo", GOOGLE_OAUTH2_BASE))
        .bearer_auth(&token)
        .send()
        .await
        .map_err(|e| format!("profile fetch failed: {}", e))?;

    if !resp.status().is_success() {
        return Err(format!("profile fetch HTTP {}", resp.status()));
    }

    let profile = resp
        .json::<GoogleProfile>()
        .await
        .map_err(|e| format!("profile parse failed: {}", e))?;

    Ok(GoogleUser {
        id: profile.id,
        display_name: profile.name.unwrap_or_else(|| "Unknown".to_string()),
        email: profile.email.unwrap_or_default(),
        image_url: profile.picture,
    })
}

async fn fetch_new_emails(
    google_state: &GoogleState,
) -> Result<Vec<(String, String, String)>, String> {
    let token = ensure_token(google_state).await?;
    let client = reqwest::Client::new();

    let list_resp = client
        .get(format!("{}/users/me/messages", GMAIL_BASE))
        .query(&[("q", "is:unread"), ("fields", "messages(id)")])
        .bearer_auth(&token)
        .send()
        .await
        .map_err(|e| format!("gmail list failed: {}", e))?;

    if !list_resp.status().is_success() {
        let status = list_resp.status();
        let body = list_resp.text().await.unwrap_or_default();
        return Err(format!("gmail list HTTP {} body: {}", status, body));
    }

    let list = list_resp
        .json::<GmailListResponse>()
        .await
        .map_err(|e| format!("gmail list parse failed: {}", e))?;

    let messages = match list.messages {
        Some(m) => m,
        None => return Ok(Vec::new()),
    };

    let mut results = Vec::new();
    for msg in &messages {
        let detail_resp = client
            .get(format!("{}/users/me/messages/{}", GMAIL_BASE, msg.id))
            .query(&[
                ("format", "metadata"),
                ("metadataHeaders", "From"),
                ("metadataHeaders", "Subject"),
            ])
            .bearer_auth(&token)
            .send()
            .await
            .map_err(|e| format!("gmail detail failed: {}", e))?;

        if !detail_resp.status().is_success() {
            continue;
        }

        let detail = detail_resp
            .json::<GmailMessageResponse>()
            .await
            .map_err(|e| format!("gmail detail parse failed: {}", e))?;

        let mut sender = String::new();
        let mut subject = String::new();

        for header in detail.payload.headers {
            match header.name.as_str() {
                "From" => {
                    sender = header.value;
                }
                "Subject" => {
                    subject = header.value;
                }
                _ => {}
            }
        }

        results.push((msg.id.clone(), sender, subject));
    }

    Ok(results)
}

async fn fetch_calendar_events(
    google_state: &GoogleState,
    last_check: &str,
) -> Result<Vec<(String, String)>, String> {
    let token = ensure_token(google_state).await?;
    let client = reqwest::Client::new();

    if last_check.is_empty() {
        return Ok(Vec::new());
    }

    let resp = client
        .get(format!("{}/calendars/primary/events", CALENDAR_BASE))
        .query(&[
            ("timeMin", last_check),
            ("singleEvents", "true"),
            ("orderBy", "start"),
            ("fields", "items(summary,organizer)"),
        ])
        .bearer_auth(&token)
        .send()
        .await
        .map_err(|e| format!("calendar fetch failed: {}", e))?;

    if !resp.status().is_success() {
        return Err(format!("calendar fetch HTTP {}", resp.status()));
    }

    let list = resp
        .json::<CalendarListResponse>()
        .await
        .map_err(|e| format!("calendar parse failed: {}", e))?;

    let items = match list.items {
        Some(i) => i,
        None => return Ok(Vec::new()),
    };

    let results: Vec<(String, String)> = items
        .into_iter()
        .map(|e| {
            let sender = e
                .organizer
                .and_then(|o| o.display_name)
                .unwrap_or_else(|| "Calendar".to_string());
            let content = e.summary.unwrap_or_else(|| "Event".to_string());
            (sender, content)
        })
        .collect();

    Ok(results)
}

// ─── Callback via local HTTP server ───────────────────────────────────────────

pub async fn start_local_server_and_wait_for_code(
    port: u16,
    expected_state: String,
) -> Result<(String, String), String> {
    let addr = format!("127.0.0.1:{}", port);
    let server = tiny_http::Server::http(&addr)
        .map_err(|e| format!("failed to start local server: {}", e))?;

    let expected = Arc::new(expected_state);
    let result = Arc::new(TokioMutex::new(None::<(String, String)>));
    let result_clone = result.clone();
    let expected_clone = expected.clone();

    let server_handle = std::thread::spawn(move || {
        for request in server.incoming_requests() {
            let url = request.url().to_string();

            let parsed = url::Url::parse(&format!("http://localhost{}", &url));
            if let Ok(parsed) = parsed {
                let state_param = parsed
                    .query_pairs()
                    .find(|(k, _)| k == "state")
                    .map(|(_, v)| v.to_string())
                    .unwrap_or_default();

                if let Some((_, code_val)) =
                    parsed.query_pairs().find(|(k, _)| k == "code")
                {
                    if state_param == *expected_clone {
                        let code = code_val.to_string();
                        let mut res = result_clone.try_lock().ok();
                        if let Some(ref mut r) = res {
                            **r = Some((code, state_param));
                        }

                        let response = tiny_http::Response::from_string(
                            "Authorization successful! You can close this window."
                                .to_string(),
                        )
                        .with_status_code(200);
                        let _ = request.respond(response);
                        return;
                    }
                }
            }

            // Rejeitar qualquer outra requisição
            let response = tiny_http::Response::from_string(
                "Invalid request".to_string(),
            )
            .with_status_code(400);
            let _ = request.respond(response);
        }
    });

    // Aguarda até 60s pelo callback
    let timeout = std::time::Duration::from_secs(60);
    let start = std::time::Instant::now();

    let result_value = loop {
        if start.elapsed() > timeout {
            return Err("OAuth timeout: no callback received within 60 seconds"
                .to_string());
        }

        let res = result.try_lock().ok();
        if let Some(mut r) = res {
            if let Some(val) = r.take() {
                break Ok(val);
            }
        }

        tokio::time::sleep(std::time::Duration::from_millis(100)).await;
    };

    let _ = server_handle;

    result_value
}

// ─── Auth URL ─────────────────────────────────────────────────────────────────

pub async fn generate_auth_url(google_state: &GoogleState) -> Result<String, String> {
    let (code_verifier, code_challenge) = generate_pkce();
    let auth_state = uuid::Uuid::new_v4().to_string();

    {
        let mut inner = google_state.inner.lock().await;
        inner.code_verifier = Some(code_verifier);
        inner.auth_state = Some(auth_state.clone());
    }

    let params = [
        ("client_id", GOOGLE_CLIENT_ID),
        ("response_type", "code"),
        ("redirect_uri", GOOGLE_REDIRECT_URI),
        ("code_challenge_method", "S256"),
        ("code_challenge", &code_challenge),
        ("state", &auth_state),
        ("scope", SCOPES),
        ("access_type", "offline"),
        ("prompt", "consent"),
    ];

    let query: String = params
        .iter()
        .map(|(k, v)| format!("{}={}", k, encode(v)))
        .collect::<Vec<_>>()
        .join("&");

    Ok(format!(
        "{}/o/oauth2/v2/auth?{}",
        GOOGLE_ACCOUNTS_BASE, query
    ))
}

// ─── State helpers ────────────────────────────────────────────────────────────

async fn emit_status(google_state: &GoogleState, app_handle: &tauri::AppHandle) {
    let inner = google_state.inner.lock().await;
    let status = GoogleStatus {
        connected: inner.connected,
        user: inner.user.clone(),
    };
    drop(inner);
    google::emit_status(app_handle, &status);
}

// ─── Watchers ─────────────────────────────────────────────────────────────────

fn start_gmail_watcher(app_handle: tauri::AppHandle) {
    tauri::async_runtime::spawn(async move {
        info!("[GOOGLE] Gmail watcher started");
        loop {
            tokio::time::sleep(std::time::Duration::from_secs(180)).await;

            let google_state = app_handle.state::<GoogleState>();
            let is_connected = {
                let inner = google_state.inner.lock().await;
                inner.connected
            };

            if !is_connected {
                continue;
            }

            let last_id = {
                let inner = google_state.inner.lock().await;
                inner.last_email_id.clone()
            };

            match fetch_new_emails(&google_state).await {
                Ok(emails) => {
                    for (id, sender, subject) in &emails {
                        if *id == last_id {
                            continue;
                        }

                        info!(
                            "[GOOGLE] new email from={}, subject={}",
                            sender, subject
                        );

                        let msg = format_command(
                            "notification",
                            &["mail", sender, subject],
                        );

                        let state = app_handle.state::<AppState>();
                        if let Err(e) = state.send_fire_forget(msg).await {
                            warn!("[GOOGLE] firmware write failed: {}", e);
                        }
                    }

                    if let Some((new_id, _, _)) = emails.first() {
                        let mut inner = google_state.inner.lock().await;
                        inner.last_email_id = new_id.clone();
                    }
                }
                Err(e) => {
                    warn!("[GOOGLE] Gmail watcher error: {}", e);
                }
            }
        }
    });
}

fn start_calendar_watcher(app_handle: tauri::AppHandle) {
    tauri::async_runtime::spawn(async move {
        info!("[GOOGLE] Calendar watcher started");
        loop {
            tokio::time::sleep(std::time::Duration::from_secs(180)).await;

            let google_state = app_handle.state::<GoogleState>();
            let is_connected = {
                let inner = google_state.inner.lock().await;
                inner.connected
            };

            if !is_connected {
                continue;
            }

            let last_check = {
                let inner = google_state.inner.lock().await;
                inner.last_calendar_check.clone()
            };

            match fetch_calendar_events(&google_state, &last_check).await {
                Ok(events) => {
                    let now = chrono_now_rfc3339();

                    for (organizer, summary) in &events {
                        info!(
                            "[GOOGLE] new calendar event: org={}, summary={}",
                            organizer, summary
                        );

                        let msg = format_command(
                            "notification",
                            &["calendar", organizer, summary],
                        );

                        // Calendar: defer de 500ms validado no HARNESS-008
                        tokio::time::sleep(std::time::Duration::from_millis(500))
                            .await;

                        let state = app_handle.state::<AppState>();
                        if let Err(e) = state.send_fire_forget(msg).await {
                            warn!("[GOOGLE] firmware write failed: {}", e);
                        }
                    }

                    if !events.is_empty() {
                        let mut inner = google_state.inner.lock().await;
                        inner.last_calendar_check = now;
                    }
                }
                Err(e) => {
                    warn!("[GOOGLE] Calendar watcher error: {}", e);
                }
            }
        }
    });
}

fn chrono_now_rfc3339() -> String {
    // ISO 8601 / RFC 3339 format without external chrono crate
    let now = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap();
    let secs = now.as_secs();
    // Simple formatting: 2026-07-11T21:33:57Z
    let days = secs / 86400;
    let time_secs = secs % 86400;
    let hours = time_secs / 3600;
    let minutes = (time_secs % 3600) / 60;
    let seconds = time_secs % 60;

    // Days since epoch to date (simplified, sufficient for Google API)
    let (year, month, day) = days_to_date(days);
    format!(
        "{:04}-{:02}-{:02}T{:02}:{:02}:{:02}Z",
        year, month, day, hours, minutes, seconds
    )
}

fn days_to_date(days: u64) -> (u64, u64, u64) {
    let mut y = 1970u64;
    let mut d = days;
    loop {
        let days_in_year = if is_leap(y) { 366 } else { 365 };
        if d < days_in_year {
            break;
        }
        d -= days_in_year;
        y += 1;
    }
    let mut m = 1u64;
    loop {
        let days_in_month = match m {
            1 | 3 | 5 | 7 | 8 | 10 | 12 => 31,
            4 | 6 | 9 | 11 => 30,
            2 => {
                if is_leap(y) {
                    29
                } else {
                    28
                }
            }
            _ => unreachable!(),
        };
        if d < days_in_month {
            break;
        }
        d -= days_in_month;
        m += 1;
    }
    (y, m, d + 1)
}

fn is_leap(year: u64) -> bool {
    (year % 4 == 0 && year % 100 != 0) || year % 400 == 0
}

// ─── Persistence ──────────────────────────────────────────────────────────────

async fn load_refresh_token(app_handle: &tauri::AppHandle) -> Option<String> {
    let mut path = app_handle.path().app_data_dir().ok()?;
    path.push("google_token.json");
    let data = std::fs::read_to_string(&path).ok()?;
    let file: crate::models::google::GoogleTokenFile =
        serde_json::from_str(&data).ok()?;
    Some(file.refresh_token)
}

async fn save_refresh_token(app_handle: &tauri::AppHandle, token: &str) {
    let mut path = match app_handle.path().app_data_dir() {
        Ok(p) => p,
        Err(e) => {
            warn!("[GOOGLE] cannot get app data dir: {}", e);
            return;
        }
    };

    std::fs::create_dir_all(&path).ok();
    path.push("google_token.json");

    let file = crate::models::google::GoogleTokenFile {
        refresh_token: token.to_string(),
    };

    let data = match serde_json::to_string_pretty(&file) {
        Ok(d) => d,
        Err(e) => {
            warn!("[GOOGLE] failed to serialize token: {}", e);
            return;
        }
    };

    if let Err(e) = std::fs::write(&path, &data) {
        warn!("[GOOGLE] failed to save token: {}", e);
    } else {
        info!("[GOOGLE] refresh token saved");
    }
}

// ─── Public API ───────────────────────────────────────────────────────────────

pub async fn connect(
    google_state: &GoogleState,
    app_handle: &tauri::AppHandle,
) -> Result<String, String> {
    let (code_verifier, code_challenge) = generate_pkce();
    let auth_state = uuid::Uuid::new_v4().to_string();

    let auth_url = {
        let params = [
            ("client_id", GOOGLE_CLIENT_ID),
            ("response_type", "code"),
            ("redirect_uri", GOOGLE_REDIRECT_URI),
            ("code_challenge_method", "S256"),
            ("code_challenge", &code_challenge),
            ("state", &auth_state),
            ("scope", SCOPES),
            ("access_type", "offline"),
            ("prompt", "consent"),
        ];

        let query: String = params
            .iter()
            .map(|(k, v)| format!("{}={}", k, encode(v)))
            .collect::<Vec<_>>()
            .join("&");

        format!(
            "{}/o/oauth2/v2/auth?{}",
            GOOGLE_ACCOUNTS_BASE, query
        )
    };

    // Open auth URL in browser
    let _ = app_handle.opener().open_url(&auth_url, None::<&str>);

    // Start local server and wait for callback
    let port = parse_redirect_port(GOOGLE_REDIRECT_URI)?;
    let (code, received_state) =
        start_local_server_and_wait_for_code(port, auth_state.clone()).await?;

    if received_state != auth_state {
        return Err("OAuth state mismatch — possible CSRF".to_string());
    }

    // Store code_verifier for exchange
    {
        let mut inner = google_state.inner.lock().await;
        inner.code_verifier = Some(code_verifier);
    }

    handle_callback(&code, google_state, app_handle).await?;

    Ok("connected".to_string())
}

async fn handle_callback(
    code: &str,
    google_state: &GoogleState,
    app_handle: &tauri::AppHandle,
) -> Result<(), String> {
    info!("[GOOGLE] callback received");

    let code_verifier = {
        let inner = google_state.inner.lock().await;
        inner.code_verifier.clone().unwrap_or_default()
    };

    let token_response = exchange_code(code, &code_verifier).await?;
    info!("[GOOGLE] tokens obtained");

    let expires_at = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_secs()
        + token_response.expires_in;

    {
        let mut inner = google_state.inner.lock().await;
        inner.access_token = Some(token_response.access_token);
        inner.refresh_token = token_response.refresh_token.clone();
        inner.expires_at = expires_at;
        inner.code_verifier = None;
        inner.auth_state = None;
    }

    if let Some(ref_token) = &token_response.refresh_token {
        save_refresh_token(app_handle, ref_token).await;
    }

    match fetch_user_profile(google_state).await {
        Ok(user) => {
            info!("[GOOGLE] logged in as {}", user.display_name);
            let mut inner = google_state.inner.lock().await;
            inner.user = Some(user);
            inner.connected = true;
            // Initialize watcher state
            let now = chrono_now_rfc3339();
            inner.last_calendar_check = now;
            drop(inner);
            emit_status(google_state, app_handle).await;
            start_gmail_watcher(app_handle.clone());
            start_calendar_watcher(app_handle.clone());
        }
        Err(e) => {
            warn!("[GOOGLE] failed to fetch profile: {}", e);
            let mut inner = google_state.inner.lock().await;
            inner.connected = false;
            drop(inner);
            emit_status(google_state, app_handle).await;
            return Err(e);
        }
    }

    Ok(())
}

pub async fn disconnect(google_state: &GoogleState, app_handle: &tauri::AppHandle) {
    {
        let mut inner = google_state.inner.lock().await;
        inner.access_token = None;
        inner.refresh_token = None;
        inner.expires_at = 0;
        inner.user = None;
        inner.connected = false;
        inner.last_email_id = String::new();
        inner.last_calendar_check = String::new();
    }

    if let Ok(mut path) = app_handle.path().app_data_dir() {
        path.push("google_token.json");
        std::fs::remove_file(&path).ok();
    }

    emit_status(google_state, app_handle).await;
    info!("[GOOGLE] disconnected");
}

pub async fn init(app_handle: tauri::AppHandle) {
    let google_state = app_handle.state::<GoogleState>();

    let saved_token = load_refresh_token(&app_handle).await;
    if let Some(ref_token) = saved_token {
        info!("[GOOGLE] restoring session from saved token");
        {
            let mut inner = google_state.inner.lock().await;
            inner.refresh_token = Some(ref_token);
        }

        match fetch_user_profile(&google_state).await {
            Ok(user) => {
                info!("[GOOGLE] session restored for {}", user.display_name);
                let mut inner = google_state.inner.lock().await;
                inner.user = Some(user);
                inner.connected = true;
                let now = chrono_now_rfc3339();
                inner.last_calendar_check = now;
                drop(inner);
                emit_status(&google_state, &app_handle).await;
                start_gmail_watcher(app_handle.clone());
                start_calendar_watcher(app_handle.clone());
            }
            Err(e) => {
                warn!("[GOOGLE] session restore failed: {}", e);
                {
                    let mut inner = google_state.inner.lock().await;
                    inner.refresh_token = None;
                    inner.connected = false;
                }
                if let Ok(mut path) = app_handle.path().app_data_dir() {
                    path.push("google_token.json");
                    std::fs::remove_file(&path).ok();
                }
                emit_status(&google_state, &app_handle).await;
            }
        }
    }

    info!("[GOOGLE] service initialized");
}

// ─── Diagnostic ───────────────────────────────────────────────────────────────

use crate::models::google::{DiagnosticMessage, GmailCheckDiagnostic};

async fn fetch_message_ids_only(
    google_state: &GoogleState,
) -> Result<Vec<String>, String> {
    let token = ensure_token(google_state).await?;
    let client = reqwest::Client::new();

    let resp = client
        .get(format!("{}/users/me/messages", GMAIL_BASE))
        .query(&[("q", "is:unread"), ("fields", "messages(id)")])
        .bearer_auth(&token)
        .send()
        .await
        .map_err(|e| format!("gmail list failed: {}", e))?;

    if !resp.status().is_success() {
        let status = resp.status();
        let body = resp.text().await.unwrap_or_default();
        return Err(format!("gmail list HTTP {} body: {}", status, body));
    }

    let list = resp
        .json::<GmailListResponse>()
        .await
        .map_err(|e| format!("gmail list parse failed: {}", e))?;

    Ok(list.messages.unwrap_or_default().into_iter().map(|m| m.id).collect())
}

pub async fn gmail_check_diagnostic(
    google_state: &GoogleState,
    app_handle: &tauri::AppHandle,
) -> GmailCheckDiagnostic {
    let last_id = {
        let inner = google_state.inner.lock().await;
        inner.last_email_id.clone()
    };

    let endpoint = format!("{}/users/me/messages", GMAIL_BASE);
    let query = "is:unread".to_string();

    info!("[DIAG] === Gmail Check Diagnostic ===");
    info!("[DIAG] 1. last_email_id: {:?}", last_id);
    info!("[DIAG] 2. Endpoint: {}", endpoint);
    info!("[DIAG] 2. Query: q={}", query);

    let message_ids = match fetch_message_ids_only(google_state).await {
        Ok(ids) => ids,
        Err(e) => {
            warn!("[DIAG] ID fetch failed: {}", e);
            Vec::new()
        }
    };
    info!("[DIAG] 4. IDs: {:?}", message_ids);

    match fetch_new_emails(google_state).await {
        Ok(emails) => {
            info!("[DIAG] 3. Messages returned: {}", emails.len());

            let diagnostic_messages: Vec<DiagnosticMessage> = emails
                .into_iter()
                .map(|(id, sender, subject)| {
                    info!("[DIAG] 5. From: {} | Subject: {}", sender, subject);
                    DiagnosticMessage {
                        id: id.clone(),
                        from: sender.clone(),
                        subject: subject.clone(),
                    }
                })
                .collect();

            let mut payloads = Vec::new();
            let mut send_called = false;
            let mut write_result = "not called".to_string();

            for msg in &diagnostic_messages {
                let payload = format_command(
                    "notification",
                    &["mail", &msg.from, &msg.subject],
                );
                info!("[DIAG] 6. Payload generated: {}", payload);
                payloads.push(payload.clone());

                let state = app_handle.state::<AppState>();
                send_called = true;
                info!("[DIAG] 7. send_fire_forget() called");
                match state.send_fire_forget(payload).await {
                    Ok(()) => {
                        info!("[DIAG] 8. peripheral.write() returned Ok");
                        write_result = "Ok".to_string();
                    }
                    Err(e) => {
                        warn!("[DIAG] 8. peripheral.write() failed: {}", e);
                        write_result = format!("Err({})", e);
                    }
                }
            }

            GmailCheckDiagnostic {
                timestamp: last_id,
                endpoint,
                query,
                messages_found: diagnostic_messages.len(),
                message_ids,
                messages: diagnostic_messages,
                payloads,
                send_fire_forget_called: send_called,
                peripheral_write_result: write_result,
                error: None,
            }
        }
        Err(e) => {
            warn!("[DIAG] Error: {}", e);
            GmailCheckDiagnostic {
                timestamp: last_id,
                endpoint,
                query,
                messages_found: 0,
                message_ids,
                messages: Vec::new(),
                payloads: Vec::new(),
                send_fire_forget_called: false,
                peripheral_write_result: "not called".to_string(),
                error: Some(e),
            }
        }
    }
}

fn parse_redirect_port(redirect_uri: &str) -> Result<u16, String> {
    let parsed = url::Url::parse(redirect_uri)
        .map_err(|e| format!("invalid redirect URI: {}", e))?;
    parsed
        .port()
        .ok_or_else(|| "redirect URI must include a port number".to_string())
}
