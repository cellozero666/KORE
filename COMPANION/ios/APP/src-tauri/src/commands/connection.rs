use tauri::command;

use crate::models::connection::ConnectionStatus;
use crate::state::connection::AppState;

#[command]
pub async fn connect(
    state: tauri::State<'_, AppState>,
    app_handle: tauri::AppHandle,
) -> Result<ConnectionStatus, String> {
    Ok(state.connect(&app_handle).await)
}

#[command]
pub async fn disconnect(
    state: tauri::State<'_, AppState>,
    app_handle: tauri::AppHandle,
) -> Result<ConnectionStatus, String> {
    Ok(state.disconnect(&app_handle).await)
}

#[command]
pub async fn send_command(
    state: tauri::State<'_, AppState>,
    command: String,
) -> Result<String, String> {
    state.send_command(command).await
}

#[command]
pub async fn get_connection_status(
    state: tauri::State<'_, AppState>,
) -> Result<ConnectionStatus, String> {
    Ok(state.status().await)
}
