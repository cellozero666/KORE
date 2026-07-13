use log::info;
use tauri::Manager;

use crate::models::settings::{CityResult, GeocodingResponse, LocationConfig, SettingsConfig};
use crate::state::settings::SettingsState;

const GEOCODING_BASE: &str = "https://geocoding-api.open-meteo.com/v1/search";

// ─── Persistence ─────────────────────────────────────────────────────────────

async fn load(app_handle: &tauri::AppHandle) -> Option<SettingsConfig> {
    let mut path = app_handle.path().app_data_dir().ok()?;
    path.push("settings.json");
    let data = std::fs::read_to_string(&path).ok()?;
    serde_json::from_str(&data).ok()
}

async fn save(app_handle: &tauri::AppHandle, config: &SettingsConfig) -> Result<(), String> {
    let path = app_handle
        .path()
        .app_data_dir()
        .map_err(|e| format!("cannot get app data dir: {}", e))?;
    std::fs::create_dir_all(&path).map_err(|e| format!("cannot create app data dir: {}", e))?;

    let mut file_name = path;
    file_name.push("settings.json");

    let data = serde_json::to_string_pretty(config)
        .map_err(|e| format!("cannot serialize settings: {}", e))?;
    std::fs::write(&file_name, &data).map_err(|e| format!("cannot write settings file: {}", e))?;

    info!("[SETTINGS] saved to {:?}", file_name);
    Ok(())
}

// ─── Location config helpers ─────────────────────────────────────────────────

pub async fn load_location(app_handle: &tauri::AppHandle) -> LocationConfig {
    load(app_handle)
        .await
        .map(|c| c.location)
        .unwrap_or_default()
}

pub async fn save_location(
    app_handle: &tauri::AppHandle,
    config: &LocationConfig,
) -> Result<(), String> {
    save(
        app_handle,
        &SettingsConfig {
            location: config.clone(),
        },
    )
    .await
}

// ─── City search ─────────────────────────────────────────────────────────────

pub async fn search_cities(query: &str, country_code: &str) -> Result<Vec<CityResult>, String> {
    let client = reqwest::Client::new();
    let mut params = vec![
        ("name", query),
        ("count", "10"),
        ("language", "pt"),
        ("format", "json"),
    ];

    if !country_code.is_empty() {
        params.push(("country_code", country_code));
    }

    let resp = client
        .get(GEOCODING_BASE)
        .query(&params)
        .send()
        .await
        .map_err(|e| format!("geocoding request failed: {}", e))?;

    if !resp.status().is_success() {
        let status = resp.status();
        let body = resp.text().await.unwrap_or_default();
        return Err(format!("geocoding HTTP {}: {}", status, body));
    }

    let geo = resp
        .json::<GeocodingResponse>()
        .await
        .map_err(|e| format!("geocoding parse failed: {}", e))?;

    let cities = geo
        .results
        .unwrap_or_default()
        .into_iter()
        .map(|r| CityResult {
            name: r.name,
            latitude: r.latitude,
            longitude: r.longitude,
            country: r.country,
            country_code: r.country_code,
        })
        .collect();

    Ok(cities)
}

// ─── Init ────────────────────────────────────────────────────────────────────

pub async fn init(app_handle: tauri::AppHandle) {
    let config = load_location(&app_handle).await;

    {
        let settings_state = app_handle.state::<SettingsState>();
        let mut inner = settings_state.inner.lock().await;
        inner.location_config = config;
    }

    info!("[SETTINGS] service initialized");
}
