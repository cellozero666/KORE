use log::info;
use tauri::Emitter;

use crate::models::weather::WeatherStatus;

pub const WEATHER_EVENT: &str = "weather-status";

pub fn emit_status(app_handle: &tauri::AppHandle, status: &WeatherStatus) {
    info!(
        "[WEATHER] event: city={:?}, temp={:?}",
        status.city,
        status.data.as_ref().map(|d| d.temperature)
    );
    let _ = app_handle.emit(WEATHER_EVENT, status);
}
