use tauri::command;

use crate::models::weather::WeatherStatus;
use crate::services::weather;
use crate::state::weather::WeatherState;

#[command]
pub async fn weather_fetch(
    state: tauri::State<'_, WeatherState>,
    app_handle: tauri::AppHandle,
    city: Option<String>,
    latitude: Option<f64>,
    longitude: Option<f64>,
) -> Result<(), String> {
    weather::fetch(&state, &app_handle, city, latitude, longitude).await;
    Ok(())
}

#[command]
pub async fn weather_status(
    state: tauri::State<'_, WeatherState>,
) -> Result<WeatherStatus, String> {
    let inner = state.inner.lock().await;
    Ok(WeatherStatus {
        city: inner.city.clone(),
        data: inner.data.clone(),
        last_update: inner.last_update.clone(),
    })
}

#[command]
pub async fn weather_set_location(
    state: tauri::State<'_, WeatherState>,
    app_handle: tauri::AppHandle,
    city: String,
    latitude: f64,
    longitude: f64,
) -> Result<(), String> {
    weather::set_location(&state, &app_handle, city, latitude, longitude).await;
    Ok(())
}
