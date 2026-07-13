use std::time::{SystemTime, UNIX_EPOCH};

use log::{info, warn};
use tauri::Manager;

use crate::communication::protocol::format_command;
use crate::events::weather;
use crate::models::weather::{IpInfoResponse, OpenMeteoResponse, WeatherData, WeatherStatus};
use crate::state::connection::AppState;
use crate::state::settings::SettingsState;
use crate::state::weather::WeatherState;

const OPEN_METEO_BASE: &str = "https://api.open-meteo.com/v1/forecast";
const IPINFO_URL: &str = "https://ipinfo.io/json";
const WATCHER_INTERVAL_SECS: u64 = 1200; // 20 min
const FORCE_SYNC_INTERVAL_SECS: u64 = 3600; // 1 hour

// ─── Weather code to firmware icon ──────────────────────────────────────────

fn weather_code_to_icon(code: u16) -> u8 {
    match code {
        0 => 5,       // Sun
        1..=3 => 1,   // Partly Cloud
        4..=48 => 0,  // Cloud
        49..=67 => 2, // Rain
        68..=77 => 3, // Snow
        _ => 4,       // Storm
    }
}

// ─── Location ────────────────────────────────────────────────────────────────

async fn fetch_location() -> Result<(String, f64, f64), String> {
    let client = reqwest::Client::new();
    let resp = client
        .get(IPINFO_URL)
        .send()
        .await
        .map_err(|e| format!("ipinfo request failed: {}", e))?;

    if !resp.status().is_success() {
        let status = resp.status();
        let body = resp.text().await.unwrap_or_default();
        return Err(format!("ipinfo HTTP {}: {}", status, body));
    }

    let data = resp
        .json::<IpInfoResponse>()
        .await
        .map_err(|e| format!("ipinfo parse failed: {}", e))?;

    let city = data.city.unwrap_or_else(|| "Unknown".to_string());
    let coords = data
        .loc
        .ok_or_else(|| "ipinfo: no coordinates returned".to_string())?;

    let parts: Vec<&str> = coords.split(',').collect();
    if parts.len() != 2 {
        return Err("ipinfo: invalid coordinate format".to_string());
    }

    let lat = parts[0]
        .parse::<f64>()
        .map_err(|_| "ipinfo: invalid latitude".to_string())?;
    let lon = parts[1]
        .parse::<f64>()
        .map_err(|_| "ipinfo: invalid longitude".to_string())?;

    Ok((city, lat, lon))
}

// ─── Open-Meteo ──────────────────────────────────────────────────────────────

async fn fetch_weather(lat: f64, lon: f64) -> Result<WeatherData, String> {
    let client = reqwest::Client::new();
    let lat_str = lat.to_string();
    let lon_str = lon.to_string();
    let resp = client
        .get(OPEN_METEO_BASE)
        .query(&[
            ("latitude", lat_str.as_str()),
            ("longitude", lon_str.as_str()),
            ("current", "temperature_2m,weather_code"),
            ("daily", "temperature_2m_max,temperature_2m_min"),
            ("timezone", "auto"),
        ])
        .send()
        .await
        .map_err(|e| format!("open-meteo request failed: {}", e))?;

    if !resp.status().is_success() {
        let status = resp.status();
        let body = resp.text().await.unwrap_or_default();
        return Err(format!("open-meteo HTTP {}: {}", status, body));
    }

    let data = resp
        .json::<OpenMeteoResponse>()
        .await
        .map_err(|e| format!("open-meteo parse failed: {}", e))?;

    Ok(WeatherData {
        temperature: data.current.temperature_2m,
        max_temperature: data.daily.temperature_2m_max[0],
        min_temperature: data.daily.temperature_2m_min[0],
        weather_code: data.current.weather_code,
    })
}

// ─── Payload building ────────────────────────────────────────────────────────

fn build_payload(city: &str, data: &WeatherData) -> String {
    let icon = weather_code_to_icon(data.weather_code);
    let temp = data.temperature.round() as i64;
    let hi = data.max_temperature.round() as i64;
    let low = data.min_temperature.round() as i64;

    format_command(
        "weather",
        &[
            city,
            &temp.to_string(),
            &hi.to_string(),
            &low.to_string(),
            &icon.to_string(),
        ],
    )
}

// ─── Sync to firmware ────────────────────────────────────────────────────────

async fn sync_to_firmware(app_handle: &tauri::AppHandle, payload: &str) {
    let state = app_handle.state::<AppState>();
    if let Err(e) = state.send_fire_forget(payload.to_string()).await {
        warn!("[WEATHER] firmware write failed: {}", e);
    } else {
        info!("[WEATHER] firmware: {}", payload);
    }
}

// ─── Main fetch + sync logic ─────────────────────────────────────────────────

async fn fetch_and_sync(
    weather_state: &WeatherState,
    app_handle: &tauri::AppHandle,
    force_sync: bool,
) {
    let (city, lat, lon) = {
        let inner = weather_state.inner.lock().await;
        match (&inner.city, inner.latitude, inner.longitude) {
            (Some(c), Some(la), Some(lo)) => (c.clone(), la, lo),
            _ => {
                drop(inner);
                match fetch_location().await {
                    Ok((c, la, lo)) => {
                        let mut inner = weather_state.inner.lock().await;
                        inner.city = Some(c.clone());
                        inner.latitude = Some(la);
                        inner.longitude = Some(lo);
                        (c, la, lo)
                    }
                    Err(e) => {
                        warn!("[WEATHER] location fetch failed: {}", e);
                        return;
                    }
                }
            }
        }
    };

    let weather = match fetch_weather(lat, lon).await {
        Ok(w) => w,
        Err(e) => {
            warn!("[WEATHER] weather fetch failed: {}", e);
            return;
        }
    };

    let payload = build_payload(&city, &weather);
    let now = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_secs();

    let should_sync = {
        let mut inner = weather_state.inner.lock().await;
        inner.data = Some(weather.clone());
        inner.last_update = Some(current_time_string());

        let is_different = payload != inner.last_payload;
        let force_expired = now >= inner.last_force_sync + FORCE_SYNC_INTERVAL_SECS;

        if is_different {
            inner.last_payload = payload.clone();
            inner.last_force_sync = now;
            true
        } else if force_expired || force_sync {
            inner.last_force_sync = now;
            true
        } else {
            false
        }
    };

    if should_sync {
        sync_to_firmware(app_handle, &payload).await;
    }

    // Emit status to frontend
    {
        let inner = weather_state.inner.lock().await;
        let status = WeatherStatus {
            city: inner.city.clone(),
            data: inner.data.clone(),
            last_update: inner.last_update.clone(),
        };
        drop(inner);
        weather::emit_status(app_handle, &status);
    }
}

fn current_time_string() -> String {
    let now = SystemTime::now().duration_since(UNIX_EPOCH).unwrap();
    let secs = now.as_secs();
    let hours = (secs / 3600) % 24;
    let minutes = (secs / 60) % 60;
    let seconds = secs % 60;
    format!("{:02}:{:02}:{:02}", hours, minutes, seconds)
}

// ─── Watcher ─────────────────────────────────────────────────────────────────

fn start_weather_watcher(app_handle: tauri::AppHandle) {
    tauri::async_runtime::spawn(async move {
        info!("[WEATHER] watcher started");
        loop {
            tokio::time::sleep(std::time::Duration::from_secs(WATCHER_INTERVAL_SECS)).await;

            let weather_state = app_handle.state::<WeatherState>();
            let is_initialized = {
                let inner = weather_state.inner.lock().await;
                inner.city.is_some()
            };

            if !is_initialized {
                continue;
            }

            fetch_and_sync(&weather_state, &app_handle, false).await;
        }
    });
}

// ─── Public API ──────────────────────────────────────────────────────────────

pub async fn clear_location(weather_state: &WeatherState) {
    let mut inner = weather_state.inner.lock().await;
    inner.city = None;
    inner.latitude = None;
    inner.longitude = None;
}

pub async fn fetch(
    weather_state: &WeatherState,
    app_handle: &tauri::AppHandle,
    city: Option<String>,
    lat: Option<f64>,
    lon: Option<f64>,
) {
    // If manual location provided, store it
    if let (Some(c), Some(la), Some(lo)) = (&city, lat, lon) {
        let mut inner = weather_state.inner.lock().await;
        inner.city = Some(c.clone());
        inner.latitude = Some(la);
        inner.longitude = Some(lo);
    }

    fetch_and_sync(weather_state, app_handle, true).await;
}

pub async fn set_location(
    weather_state: &WeatherState,
    app_handle: &tauri::AppHandle,
    city: String,
    lat: f64,
    lon: f64,
) {
    {
        let mut inner = weather_state.inner.lock().await;
        inner.city = Some(city);
        inner.latitude = Some(lat);
        inner.longitude = Some(lon);
    }

    // Trigger new weather fetch after setting location
    fetch_and_sync(weather_state, app_handle, true).await;
}

pub async fn init(app_handle: tauri::AppHandle) {
    info!("[WEATHER] service initialized");

    // Check Settings for saved manual location
    let settings_state = app_handle.state::<SettingsState>();
    let has_manual = {
        let inner = settings_state.inner.lock().await;
        let config = &inner.location_config;
        if !config.autodetect && !config.city.is_empty() {
            Some((config.city.clone(), config.latitude, config.longitude))
        } else {
            None
        }
    };

    // If manual location saved, preload WeatherState so IPInfo isn't called
    if let Some((city, lat, lon)) = has_manual {
        let weather_state = app_handle.state::<WeatherState>();
        let mut inner = weather_state.inner.lock().await;
        inner.city = Some(city);
        inner.latitude = Some(lat);
        inner.longitude = Some(lon);
        info!("[WEATHER] loaded manual location from settings");
    }

    start_weather_watcher(app_handle);
}
