use tauri::command;
use tauri_plugin_opener::OpenerExt;

use crate::models::spotify::SpotifyStatus;
use crate::services::spotify;
use crate::state::spotify::SpotifyState;

#[command]
pub async fn spotify_connect(
    state: tauri::State<'_, SpotifyState>,
    app_handle: tauri::AppHandle,
) -> Result<String, String> {
    let url = spotify::generate_auth_url(&state).await?;
    let _ = app_handle.opener().open_url(&url, None::<&str>);
    Ok(url)
}

#[command]
pub async fn spotify_disconnect(
    state: tauri::State<'_, SpotifyState>,
    app_handle: tauri::AppHandle,
) -> Result<(), String> {
    spotify::disconnect(&state, &app_handle).await;
    Ok(())
}

#[command]
pub async fn spotify_play(
    state: tauri::State<'_, SpotifyState>,
    app_handle: tauri::AppHandle,
) -> Result<(), String> {
    spotify::player_play(&state, &app_handle).await
}

#[command]
pub async fn spotify_pause(
    state: tauri::State<'_, SpotifyState>,
    app_handle: tauri::AppHandle,
) -> Result<(), String> {
    spotify::player_pause(&state, &app_handle).await
}

#[command]
pub async fn spotify_next(
    state: tauri::State<'_, SpotifyState>,
    app_handle: tauri::AppHandle,
) -> Result<(), String> {
    spotify::player_next(&state, &app_handle).await
}

#[command]
pub async fn spotify_previous(
    state: tauri::State<'_, SpotifyState>,
    app_handle: tauri::AppHandle,
) -> Result<(), String> {
    spotify::player_previous(&state, &app_handle).await
}

#[command]
pub async fn spotify_status(
    state: tauri::State<'_, SpotifyState>,
) -> Result<SpotifyStatus, String> {
    let inner = state.inner.lock().await;
    Ok(SpotifyStatus {
        connected: inner.connected,
        user: inner.user.clone(),
        playback: inner.playback.clone(),
    })
}
