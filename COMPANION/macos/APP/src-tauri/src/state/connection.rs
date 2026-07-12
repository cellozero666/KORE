use log::{info, warn};

use crate::communication::manager::CommunicationManager;
use crate::models::connection::ConnectionStatus;
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
