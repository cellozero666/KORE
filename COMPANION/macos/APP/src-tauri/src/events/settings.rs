use log::info;
use tauri::Emitter;

use crate::models::settings::LocationConfig;

pub const SETTINGS_EVENT: &str = "settings-updated";

pub fn emit_location(app_handle: &tauri::AppHandle, config: &LocationConfig) {
    info!(
        "[SETTINGS] event: autodetect={}, city={}",
        config.autodetect, config.city
    );
    let _ = app_handle.emit(SETTINGS_EVENT, config);
}
