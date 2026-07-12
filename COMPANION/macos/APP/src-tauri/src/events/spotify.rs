use log::info;
use tauri::Emitter;

use crate::models::spotify::SpotifyStatus;

pub const SPOTIFY_EVENT: &str = "spotify-status";

pub fn emit_status(app_handle: &tauri::AppHandle, status: &SpotifyStatus) {
    info!(
        "[SPOTIFY] event: connected={}, user={:?}",
        status.connected,
        status.user.as_ref().map(|u| &u.display_name)
    );
    let _ = app_handle.emit(SPOTIFY_EVENT, status);
}
