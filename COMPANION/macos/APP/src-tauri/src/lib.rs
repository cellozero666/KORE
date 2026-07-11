mod commands;
mod communication;
mod events;
mod models;
mod services;
mod state;

use state::connection::AppState;

#[cfg_attr(mobile, tauri::mobile_entry_point)]
pub fn run() {
    env_logger::Builder::from_env(env_logger::Env::default().default_filter_or("info"))
        .format_timestamp_millis()
        .init();

    tauri::Builder::default()
        .plugin(tauri_plugin_opener::init())
        .plugin(tauri_plugin_deep_link::init())
        .manage(AppState::new())
        .invoke_handler(tauri::generate_handler![
            commands::connection::connect,
            commands::connection::disconnect,
            commands::connection::send_command,
            commands::connection::get_connection_status,
        ])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
