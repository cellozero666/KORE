mod commands;
mod communication;
#[path = "../config/config.rs"]
mod config;
mod events;
mod models;
mod services;
mod state;

use state::connection::AppState;
use state::google::GoogleState;
use state::settings::SettingsState;
use state::spotify::SpotifyState;
use state::weather::WeatherState;

#[cfg_attr(mobile, tauri::mobile_entry_point)]
pub fn run() {
    env_logger::Builder::from_env(env_logger::Env::default().default_filter_or("info"))
        .format_timestamp_millis()
        .init();

    tauri::Builder::default()
        .plugin(tauri_plugin_opener::init())
        .plugin(tauri_plugin_deep_link::init())
        .manage(AppState::new())
        .manage(SpotifyState::new())
        .manage(GoogleState::new())
        .manage(SettingsState::new())
        .manage(WeatherState::new())
        .invoke_handler(tauri::generate_handler![
            commands::connection::connect,
            commands::connection::disconnect,
            commands::connection::send_command,
            commands::connection::get_connection_status,
            commands::spotify::spotify_connect,
            commands::spotify::spotify_disconnect,
            commands::spotify::spotify_play,
            commands::spotify::spotify_pause,
            commands::spotify::spotify_next,
            commands::spotify::spotify_previous,
            commands::spotify::spotify_status,
            commands::google::google_connect,
            commands::google::google_disconnect,
            commands::google::google_status,
            commands::weather::weather_fetch,
            commands::weather::weather_status,
            commands::weather::weather_set_location,
            commands::settings::settings_get,
            commands::settings::settings_save_location,
            commands::settings::settings_search_cities,
            commands::settings::settings_wifi_connect,
        ])
        .setup(|app| {
            let handle = app.handle().clone();
            tauri::async_runtime::spawn(async move {
                services::notifications::init(handle.clone()).await;
                services::spotify::init(handle.clone()).await;
                services::google::init(handle.clone()).await;
                services::settings::init(handle.clone()).await;
                services::weather::init(handle).await;
            });
            Ok(())
        })
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
