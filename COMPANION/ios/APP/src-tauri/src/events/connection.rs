use log::info;
use tauri::Emitter;

use crate::models::connection::ConnectionStatus;

pub const CONNECTION_EVENT: &str = "connection-status";

pub fn emit_status(app_handle: &tauri::AppHandle, status: &ConnectionStatus) {
    info!(
        "[EVENT] emitting '{}': state={:?}, transport={:?}, message={:?}",
        CONNECTION_EVENT, status.state, status.transport, status.message
    );
    let _ = app_handle.emit(CONNECTION_EVENT, status);
}
