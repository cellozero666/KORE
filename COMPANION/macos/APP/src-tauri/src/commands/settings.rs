use tauri::command;
use tauri::Manager;

use crate::communication::protocol::format_command;
use crate::events::settings;
use crate::models::settings::{CityResult, LocationConfig};
use crate::services::{settings as settings_service, weather};
use crate::state::connection::AppState;
use crate::state::settings::SettingsState;
use crate::state::weather::WeatherState;

#[command]
pub async fn settings_get(
    state: tauri::State<'_, SettingsState>,
) -> Result<LocationConfig, String> {
    let inner = state.inner.lock().await;
    Ok(inner.location_config.clone())
}

#[command]
pub async fn settings_save_location(
    state: tauri::State<'_, SettingsState>,
    app_handle: tauri::AppHandle,
    autodetect: bool,
    country: String,
    city: String,
    latitude: f64,
    longitude: f64,
) -> Result<(), String> {
    let config = LocationConfig {
        autodetect,
        country,
        city,
        latitude,
        longitude,
    };

    // Persist
    settings_service::save_location(&app_handle, &config).await?;

    // Update state
    {
        let mut inner = state.inner.lock().await;
        inner.location_config = config.clone();
    }

    // Integrate with Weather
    if autodetect {
        let weather_state = app_handle.state::<WeatherState>();
        weather::clear_location(&weather_state).await;
        weather::fetch(&weather_state, &app_handle, None, None, None).await;
    } else {
        let weather_state = app_handle.state::<WeatherState>();
        weather::set_location(
            &weather_state,
            &app_handle,
            config.city.clone(),
            config.latitude,
            config.longitude,
        )
        .await;
    }

    // Emit to frontend
    settings::emit_location(&app_handle, &config);

    Ok(())
}

#[command]
pub async fn settings_search_cities(
    query: String,
    country_code: String,
) -> Result<Vec<CityResult>, String> {
    settings_service::search_cities(&query, &country_code).await
}

#[command]
pub async fn settings_wifi_connect(
    app_handle: tauri::AppHandle,
    ssid: String,
    password: String,
) -> Result<(), String> {
    let payload = format_command("wifi_connect", &[&ssid, &password]);
    let state = app_handle.state::<AppState>();
    state.send_fire_forget(payload).await
}
