use chrono::Timelike;
use log::{info, warn};
use tauri::Manager;

use crate::communication::manager::CommunicationManager;
use crate::communication::protocol;
use crate::models::connection::{ConnectionState, ConnectionStatus};
use tokio::sync::Mutex;

pub struct AppState {
    pub manager: Mutex<CommunicationManager>,
}

impl AppState {
    pub fn new() -> Self {
        AppState {
            manager: Mutex::new(CommunicationManager::new()),
        }
    }

    pub async fn connect(&self, app_handle: &tauri::AppHandle) -> ConnectionStatus {
        let mut manager = self.manager.lock().await;

        if manager.is_connected() {
            let status = manager.status();
            return status;
        }

        crate::events::connection::emit_status(app_handle, &ConnectionStatus::connecting("BLE"));

        match manager.connect().await {
            Ok(status) => {
                info!(
                    "connect succeeded: state={:?}, transport={:?}",
                    status.state, status.transport
                );
                crate::events::connection::emit_status(app_handle, &status);

                // Background clock sync — watches for hour changes
                let handle = app_handle.clone();
                tokio::spawn(async move {
                    clock_sync_loop(handle).await;
                });

                status
            }
            Err(msg) => {
                warn!("connect failed: {}", msg);
                let error_status = ConnectionStatus::error(&msg);
                crate::events::connection::emit_status(app_handle, &error_status);
                error_status
            }
        }
    }

    pub async fn disconnect(&self, app_handle: &tauri::AppHandle) -> ConnectionStatus {
        let mut manager = self.manager.lock().await;
        let _ = manager.disconnect().await;
        let status = ConnectionStatus::disconnected();
        crate::events::connection::emit_status(app_handle, &status);
        status
    }

    pub async fn send_command(&self, command: String) -> Result<String, String> {
        let mut manager = self.manager.lock().await;
        manager.send_command(&command).await
    }

    /// Send a command without waiting for a response (fire-and-forget).
    /// Used for notifications where the firmware does not reply.
    pub async fn send_fire_forget(&self, command: String) -> Result<(), String> {
        let mut manager = self.manager.lock().await;
        manager.send_fire_forget(&command).await
    }

    pub async fn status(&self) -> ConnectionStatus {
        let manager = self.manager.lock().await;
        manager.status()
    }
}

/// Background task that monitors the local hour and sends `time|HH|MM|SS`
/// whenever the hour changes. Self-terminates on disconnect.
async fn clock_sync_loop(app_handle: tauri::AppHandle) {
    let mut last_hour: Option<u32> = None;

    loop {
        tokio::time::sleep(std::time::Duration::from_secs(30)).await;

        let state = app_handle.state::<AppState>();
        {
            let manager = state.manager.lock().await;
            if manager.status().state != ConnectionState::Connected {
                warn!("[TIME] connection lost, stopping clock sync");
                break;
            }
        }

        let current_hour = chrono::Local::now().hour();

        if last_hour.map_or(true, |h| h != current_hour) {
            let cmd = protocol::format_time_command();
            match state.send_command(cmd).await {
                Ok(resp) => info!("[TIME] hourly sync: {}", resp.trim()),
                Err(e) => warn!("[TIME] hourly sync failed: {}", e),
            }
            last_hour = Some(current_hour);
        }
    }
}
