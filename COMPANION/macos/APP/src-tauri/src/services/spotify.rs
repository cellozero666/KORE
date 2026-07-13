use std::time::{SystemTime, UNIX_EPOCH};

use log::{info, warn};
use tauri::Manager;
use urlencoding::encode;

use crate::communication::protocol::format_command;
use crate::config::{SPOTIFY_CLIENT_ID, SPOTIFY_REDIRECT_URI};
use crate::events::spotify;
use crate::models::spotify::{
    RefreshTokenFile, SpotifyPlayback, SpotifyStatus, SpotifyTokenResponse, SpotifyUser,
};
use crate::state::connection::AppState;
use crate::state::spotify::SpotifyState;

const SPOTIFY_API_BASE: &str = "https://api.spotify.com/v1";
const SPOTIFY_ACCOUNTS_BASE: &str = "https://accounts.spotify.com";
const SCOPES: &str = "user-read-private user-read-email user-read-playback-state user-read-currently-playing user-modify-playback-state";

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

// ─── API types (private) ──────────────────────────────────────────────────────

#[derive(serde::Deserialize)]
struct ApiImage {
    url: String,
}

#[derive(serde::Deserialize)]
struct ApiArtist {
    name: String,
}

#[derive(serde::Deserialize)]
struct ApiAlbum {
    name: String,
    #[serde(default)]
    images: Vec<ApiImage>,
}

#[derive(serde::Deserialize)]
struct ApiTrackItem {
    name: String,
    #[serde(default)]
    artists: Vec<ApiArtist>,
    album: ApiAlbum,
    duration_ms: u64,
}

#[derive(serde::Deserialize)]
struct ApiProfile {
    id: String,
    display_name: Option<String>,
    images: Vec<ApiImage>,
}

// ─── OAuth helpers ────────────────────────────────────────────────────────────

async fn exchange_code(code: &str, code_verifier: &str) -> Result<SpotifyTokenResponse, String> {
    let client = reqwest::Client::new();
    let params = [
        ("grant_type", "authorization_code"),
        ("code", code),
        ("redirect_uri", SPOTIFY_REDIRECT_URI),
        ("client_id", SPOTIFY_CLIENT_ID),
        ("code_verifier", code_verifier),
    ];

    let resp = client
        .post(format!("{}/api/token", SPOTIFY_ACCOUNTS_BASE))
        .form(&params)
        .send()
        .await
        .map_err(|e| format!("token exchange request failed: {}", e))?;

    if !resp.status().is_success() {
        let status = resp.status();
        let body = resp.text().await.unwrap_or_default();
        return Err(format!("token exchange failed ({}): {}", status, body));
    }

    resp.json::<SpotifyTokenResponse>()
        .await
        .map_err(|e| format!("token exchange parse failed: {}", e))
}

async fn refresh_access_token(refresh_token: &str) -> Result<SpotifyTokenResponse, String> {
    let client = reqwest::Client::new();
    let params = [
        ("grant_type", "refresh_token"),
        ("refresh_token", refresh_token),
        ("client_id", SPOTIFY_CLIENT_ID),
    ];

    let resp = client
        .post(format!("{}/api/token", SPOTIFY_ACCOUNTS_BASE))
        .form(&params)
        .send()
        .await
        .map_err(|e| format!("token refresh request failed: {}", e))?;

    if !resp.status().is_success() {
        let status = resp.status();
        let body = resp.text().await.unwrap_or_default();
        return Err(format!("token refresh failed ({}): {}", status, body));
    }

    let mut token: SpotifyTokenResponse = resp
        .json()
        .await
        .map_err(|e| format!("token refresh parse failed: {}", e))?;

    if token.refresh_token.is_none() {
        token.refresh_token = Some(refresh_token.to_string());
    }

    Ok(token)
}

async fn ensure_token(
    spotify_state: &SpotifyState,
    app_handle: &tauri::AppHandle,
) -> Result<String, String> {
    let mut inner = spotify_state.inner.lock().await;

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
            save_refresh_token(app_handle, new_refresh).await;
        }
    }

    Ok(token_response.access_token)
}

// ─── API calls ────────────────────────────────────────────────────────────────

async fn fetch_user_profile(
    spotify_state: &SpotifyState,
    app_handle: &tauri::AppHandle,
) -> Result<SpotifyUser, String> {
    let token = ensure_token(spotify_state, app_handle).await?;
    let client = reqwest::Client::new();

    let resp = client
        .get(format!("{}/me", SPOTIFY_API_BASE))
        .bearer_auth(&token)
        .send()
        .await
        .map_err(|e| format!("profile fetch failed: {}", e))?;

    if !resp.status().is_success() {
        return Err(format!("profile fetch HTTP {}", resp.status()));
    }

    let profile = resp
        .json::<ApiProfile>()
        .await
        .map_err(|e| format!("profile parse failed: {}", e))?;

    Ok(SpotifyUser {
        id: profile.id,
        display_name: profile
            .display_name
            .unwrap_or_else(|| "Unknown".to_string()),
        image_url: profile.images.into_iter().next().map(|img| img.url),
    })
}

fn parse_track_response(progress_ms: u64, is_playing: bool, item: ApiTrackItem) -> SpotifyPlayback {
    let artist = item
        .artists
        .into_iter()
        .map(|a| a.name)
        .collect::<Vec<_>>()
        .join(", ");

    SpotifyPlayback {
        track: item.name,
        artist,
        album: item.album.name,
        album_art: item.album.images.into_iter().next().map(|img| img.url),
        progress_ms,
        duration_ms: item.duration_ms,
        is_playing,
    }
}

async fn fetch_currently_playing(
    spotify_state: &SpotifyState,
    app_handle: &tauri::AppHandle,
) -> Result<Option<SpotifyPlayback>, String> {
    let token = ensure_token(spotify_state, app_handle).await?;
    let client = reqwest::Client::new();

    let resp = client
        .get(format!("{}/me/player", SPOTIFY_API_BASE))
        .bearer_auth(&token)
        .send()
        .await
        .map_err(|e| format!("playback fetch failed: {}", e))?;

    if resp.status() == reqwest::StatusCode::NO_CONTENT {
        return Ok(None);
    }

    if !resp.status().is_success() {
        return Err(format!("playback fetch HTTP {}", resp.status()));
    }

    #[derive(serde::Deserialize)]
    struct ApiPlayback {
        progress_ms: u64,
        is_playing: bool,
        item: ApiTrackItem,
    }

    let playback = resp
        .json::<ApiPlayback>()
        .await
        .map_err(|e| format!("playback parse failed: {}", e))?;

    Ok(Some(parse_track_response(
        playback.progress_ms,
        playback.is_playing,
        playback.item,
    )))
}

async fn api_post_empty(
    spotify_state: &SpotifyState,
    app_handle: &tauri::AppHandle,
    path: &str,
) -> Result<(), String> {
    let token = ensure_token(spotify_state, app_handle).await?;
    let client = reqwest::Client::new();

    let url = format!("{}{}", SPOTIFY_API_BASE, path);
    let resp = client
        .post(&url)
        .bearer_auth(&token)
        .header(reqwest::header::CONTENT_TYPE, "application/json")
        .body("{}")
        .send()
        .await
        .map_err(|e| format!("POST {} failed: {}", path, e))?;

    let status = resp.status();
    if !status.is_success() && status != reqwest::StatusCode::NO_CONTENT {
        let body = resp.text().await.unwrap_or_default();
        return Err(format!("POST {} HTTP {}: {}", path, status, body));
    }

    Ok(())
}

async fn api_put_empty(
    spotify_state: &SpotifyState,
    app_handle: &tauri::AppHandle,
    path: &str,
) -> Result<(), String> {
    let token = ensure_token(spotify_state, app_handle).await?;
    let client = reqwest::Client::new();

    let url = format!("{}{}", SPOTIFY_API_BASE, path);
    let resp = client
        .put(&url)
        .bearer_auth(&token)
        .header(reqwest::header::CONTENT_TYPE, "application/json")
        .body("{}")
        .send()
        .await
        .map_err(|e| format!("PUT {} failed: {}", path, e))?;

    let status = resp.status();
    if !status.is_success() && status != reqwest::StatusCode::NO_CONTENT {
        let body = resp.text().await.unwrap_or_default();
        return Err(format!("PUT {} HTTP {}: {}", path, status, body));
    }

    Ok(())
}

pub async fn player_play(
    spotify_state: &SpotifyState,
    app_handle: &tauri::AppHandle,
) -> Result<(), String> {
    api_put_empty(spotify_state, app_handle, "/me/player/play").await
}

pub async fn player_pause(
    spotify_state: &SpotifyState,
    app_handle: &tauri::AppHandle,
) -> Result<(), String> {
    api_put_empty(spotify_state, app_handle, "/me/player/pause").await
}

pub async fn player_next(
    spotify_state: &SpotifyState,
    app_handle: &tauri::AppHandle,
) -> Result<(), String> {
    api_post_empty(spotify_state, app_handle, "/me/player/next").await
}

pub async fn player_previous(
    spotify_state: &SpotifyState,
    app_handle: &tauri::AppHandle,
) -> Result<(), String> {
    api_post_empty(spotify_state, app_handle, "/me/player/previous").await
}

// ─── OAuth flow ───────────────────────────────────────────────────────────────

pub async fn generate_auth_url(spotify_state: &SpotifyState) -> Result<String, String> {
    let (code_verifier, code_challenge) = generate_pkce();
    let auth_state = uuid::Uuid::new_v4().to_string();

    {
        let mut inner = spotify_state.inner.lock().await;
        inner.code_verifier = Some(code_verifier);
        inner.auth_state = Some(auth_state.clone());
    }

    let params = [
        ("client_id", SPOTIFY_CLIENT_ID),
        ("response_type", "code"),
        ("redirect_uri", SPOTIFY_REDIRECT_URI),
        ("code_challenge_method", "S256"),
        ("code_challenge", &code_challenge),
        ("state", &auth_state),
        ("scope", SCOPES),
    ];

    let query: String = params
        .iter()
        .map(|(k, v)| format!("{}={}", k, encode(v)))
        .collect::<Vec<_>>()
        .join("&");

    Ok(format!("{}/authorize?{}", SPOTIFY_ACCOUNTS_BASE, query))
}

pub async fn handle_callback(
    url: &str,
    spotify_state: &SpotifyState,
    app_handle: &tauri::AppHandle,
) -> Result<(), String> {
    info!("[SPOTIFY] callback received");

    let parsed = url::Url::parse(url).map_err(|e| format!("invalid callback URL: {}", e))?;

    let error_param = parsed
        .query_pairs()
        .find(|(k, _)| k == "error")
        .map(|(_, v)| v.to_string());

    if let Some(err) = error_param {
        return Err(format!("Spotify OAuth error: {}", err));
    }

    let code = parsed
        .query_pairs()
        .find(|(k, _)| k == "code")
        .map(|(_, v)| v.to_string())
        .ok_or_else(|| "missing code parameter".to_string())?;

    let state_param = parsed
        .query_pairs()
        .find(|(k, _)| k == "state")
        .map(|(_, v)| v.to_string())
        .ok_or_else(|| "missing state parameter".to_string())?;

    let (stored_state, code_verifier) = {
        let inner = spotify_state.inner.lock().await;
        (
            inner.auth_state.clone().unwrap_or_default(),
            inner.code_verifier.clone().unwrap_or_default(),
        )
    };

    if state_param != stored_state {
        return Err("OAuth state mismatch — possible CSRF".to_string());
    }

    let token_response = exchange_code(&code, &code_verifier).await?;
    info!("[SPOTIFY] tokens obtained");

    let expires_at = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_secs()
        + token_response.expires_in;

    {
        let mut inner = spotify_state.inner.lock().await;
        inner.access_token = Some(token_response.access_token);
        inner.refresh_token = token_response.refresh_token.clone();
        inner.expires_at = expires_at;
        inner.code_verifier = None;
        inner.auth_state = None;
    }

    if let Some(ref_token) = &token_response.refresh_token {
        save_refresh_token(app_handle, ref_token).await;
    }

    match fetch_user_profile(spotify_state, app_handle).await {
        Ok(user) => {
            info!("[SPOTIFY] logged in as {}", user.display_name);
            let mut inner = spotify_state.inner.lock().await;
            inner.user = Some(user);
            inner.connected = true;
        }
        Err(e) => {
            warn!("[SPOTIFY] failed to fetch profile: {}", e);
        }
    }

    emit_status(spotify_state, app_handle).await;
    start_watcher(app_handle.clone());

    Ok(())
}

// ─── State helpers ────────────────────────────────────────────────────────────

async fn emit_status(spotify_state: &SpotifyState, app_handle: &tauri::AppHandle) {
    let inner = spotify_state.inner.lock().await;
    let status = SpotifyStatus {
        connected: inner.connected,
        user: inner.user.clone(),
        playback: inner.playback.clone(),
    };
    drop(inner);
    spotify::emit_status(app_handle, &status);
}

// ─── Watcher ──────────────────────────────────────────────────────────────────

async fn update_playback_and_sync(spotify_state: &SpotifyState, app_handle: &tauri::AppHandle) {
    let playback = match fetch_currently_playing(spotify_state, app_handle).await {
        Ok(Some(p)) => Some(p),
        Ok(None) => None,
        Err(e) => {
            warn!("[SPOTIFY] watcher: {}", e);
            return;
        }
    };

    let (was_playing, track_changed) = {
        let inner = spotify_state.inner.lock().await;
        let track_changed = match (&inner.playback, &playback) {
            (Some(old), Some(new)) => old.track != new.track,
            _ => true,
        };
        (inner.was_playing, track_changed)
    };

    let is_playing = playback.as_ref().map(|p| p.is_playing).unwrap_or(false);

    // Sync with firmware
    let state_lock = app_handle.state::<AppState>();
    let mut manager = state_lock.manager.lock().await;

    if let Some(ref pb) = playback {
        if is_playing {
            let msg = format_command(
                "spotify",
                &[
                    &pb.track,
                    &pb.artist,
                    &pb.album,
                    &pb.progress_ms.to_string(),
                    &pb.duration_ms.to_string(),
                ],
            );
            if track_changed || !was_playing {
                info!("[SPOTIFY] firmware: track change -> {}", msg);
            }
            if let Err(e) = manager.send_fire_forget(&msg).await {
                warn!("[SPOTIFY] firmware write failed: {}", e);
            }
        }
    } else if was_playing {
        info!("[SPOTIFY] firmware: stop");
        if let Err(e) = manager.send_fire_forget("spotify_stop").await {
            warn!("[SPOTIFY] firmware write failed: {}", e);
        }
    }

    drop(manager);

    // Update internal state
    {
        let mut inner = spotify_state.inner.lock().await;
        inner.playback = playback;
        inner.was_playing = is_playing;
    }

    emit_status(spotify_state, app_handle).await;
}

fn start_watcher(app_handle: tauri::AppHandle) {
    tauri::async_runtime::spawn(async move {
        info!("[SPOTIFY] watcher started");
        loop {
            tokio::time::sleep(std::time::Duration::from_secs(5)).await;

            let spotify_state = app_handle.state::<SpotifyState>();
            let is_connected = {
                let inner = spotify_state.inner.lock().await;
                inner.connected
            };

            if !is_connected {
                continue;
            }

            update_playback_and_sync(&spotify_state, &app_handle).await;
        }
    });
}

// ─── Persistence ──────────────────────────────────────────────────────────────

async fn load_refresh_token(app_handle: &tauri::AppHandle) -> Option<String> {
    let mut path = app_handle.path().app_data_dir().ok()?;
    path.push("spotify_token.json");
    let data = std::fs::read_to_string(&path).ok()?;
    let file: RefreshTokenFile = serde_json::from_str(&data).ok()?;
    Some(file.refresh_token)
}

async fn save_refresh_token(app_handle: &tauri::AppHandle, token: &str) {
    let mut path = match app_handle.path().app_data_dir() {
        Ok(p) => p,
        Err(e) => {
            warn!("[SPOTIFY] cannot get app data dir: {}", e);
            return;
        }
    };

    std::fs::create_dir_all(&path).ok();
    path.push("spotify_token.json");

    let file = RefreshTokenFile {
        refresh_token: token.to_string(),
    };

    let data = match serde_json::to_string_pretty(&file) {
        Ok(d) => d,
        Err(e) => {
            warn!("[SPOTIFY] failed to serialize token: {}", e);
            return;
        }
    };

    if let Err(e) = std::fs::write(&path, &data) {
        warn!("[SPOTIFY] failed to save token: {}", e);
    } else {
        info!("[SPOTIFY] refresh token saved");
    }
}

// ─── Public API ───────────────────────────────────────────────────────────────

pub async fn disconnect(spotify_state: &SpotifyState, app_handle: &tauri::AppHandle) {
    {
        let mut inner = spotify_state.inner.lock().await;
        inner.access_token = None;
        inner.refresh_token = None;
        inner.expires_at = 0;
        inner.user = None;
        inner.playback = None;
        inner.connected = false;
        inner.was_playing = false;
    }

    if let Ok(mut path) = app_handle.path().app_data_dir() {
        path.push("spotify_token.json");
        std::fs::remove_file(&path).ok();
    }

    emit_status(spotify_state, app_handle).await;
    info!("[SPOTIFY] disconnected");
}

pub async fn init(app_handle: tauri::AppHandle) {
    let spotify_state = app_handle.state::<SpotifyState>();

    // Try to restore session from saved refresh_token
    let saved_token = load_refresh_token(&app_handle).await;
    if let Some(ref_token) = saved_token {
        info!("[SPOTIFY] restoring session from saved token");
        {
            let mut inner = spotify_state.inner.lock().await;
            inner.refresh_token = Some(ref_token);
        }

        match fetch_user_profile(&spotify_state, &app_handle).await {
            Ok(user) => {
                info!("[SPOTIFY] session restored for {}", user.display_name);
                let mut inner = spotify_state.inner.lock().await;
                inner.user = Some(user);
                inner.connected = true;
                drop(inner);
                emit_status(&spotify_state, &app_handle).await;
                start_watcher(app_handle.clone());
            }
            Err(e) => {
                warn!("[SPOTIFY] session restore failed: {}", e);
                {
                    let mut inner = spotify_state.inner.lock().await;
                    inner.refresh_token = None;
                    inner.connected = false;
                }
                if let Ok(mut path) = app_handle.path().app_data_dir() {
                    path.push("spotify_token.json");
                    std::fs::remove_file(&path).ok();
                }
            }
        }
    }

    // Register deep-link handler for OAuth callback
    {
        use tauri_plugin_deep_link::DeepLinkExt;
        let handle = app_handle.clone();

        app_handle.deep_link().on_open_url(move |event| {
            let h = handle.clone();
            for url in event.urls() {
                let h2 = h.clone();
                let url_str = url.to_string();
                tauri::async_runtime::spawn(async move {
                    let spotify_state = h2.state::<SpotifyState>();
                    if let Err(e) = handle_callback(&url_str, &spotify_state, &h2).await {
                        warn!("[SPOTIFY] callback error: {}", e);
                        emit_status(&h2.state::<SpotifyState>(), &h2).await;
                    }
                });
            }
        });
    }

    info!("[SPOTIFY] service initialized");
}
