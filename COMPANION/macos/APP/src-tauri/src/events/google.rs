use log::info;
use tauri::Emitter;

use crate::models::google::GoogleStatus;

pub const GOOGLE_EVENT: &str = "google-status";

pub fn emit_status(app_handle: &tauri::AppHandle, status: &GoogleStatus) {
    info!(
        "[GOOGLE] event: connected={}, user={:?}",
        status.connected,
        status.user.as_ref().map(|u| &u.display_name)
    );
    let _ = app_handle.emit(GOOGLE_EVENT, status);
}
