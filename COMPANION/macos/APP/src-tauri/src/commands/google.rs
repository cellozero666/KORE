use tauri::command;

use crate::models::google::{GmailCheckDiagnostic, GoogleStatus};
use crate::services::google;
use crate::state::google::GoogleState;

#[command]
pub async fn google_connect(
    state: tauri::State<'_, GoogleState>,
    app_handle: tauri::AppHandle,
) -> Result<String, String> {
    google::connect(&state, &app_handle).await
}

#[command]
pub async fn google_disconnect(
    state: tauri::State<'_, GoogleState>,
    app_handle: tauri::AppHandle,
) -> Result<(), String> {
    google::disconnect(&state, &app_handle).await;
    Ok(())
}

#[command]
pub async fn google_status(
    state: tauri::State<'_, GoogleState>,
) -> Result<GoogleStatus, String> {
    let inner = state.inner.lock().await;
    Ok(GoogleStatus {
        connected: inner.connected,
        user: inner.user.clone(),
    })
}

#[command]
pub async fn gmail_check_diagnostic(
    state: tauri::State<'_, GoogleState>,
    app_handle: tauri::AppHandle,
) -> Result<GmailCheckDiagnostic, String> {
    Ok(google::gmail_check_diagnostic(&state, &app_handle).await)
}
