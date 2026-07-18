use log::{error, info, warn};
use tauri::Emitter;

use super::ble::BleTransport;
use super::handshake::{perform_handshake, Transport};
use super::types::TransportType;

use crate::models::connection::{ConnectionState, ConnectionStatus};

pub struct CommunicationManager {
    ble: BleTransport,
    serial: crate::communication::serial::SerialTransport,
    active: Option<TransportType>,
    state: ConnectionState,
    error_message: Option<String>,
    step: Option<String>,
    app_handle: Option<tauri::AppHandle>,
}

impl CommunicationManager {
    pub fn new() -> Self {
        info!("[MANAGER] CommunicationManager created");
        CommunicationManager {
            ble: BleTransport::new(),
            serial: crate::communication::serial::SerialTransport::new(),
            active: None,
            state: ConnectionState::Disconnected,
            error_message: None,
            step: None,
            app_handle: None,
        }
    }

    pub fn set_app_handle(&mut self, handle: tauri::AppHandle) {
        self.app_handle = Some(handle);
    }

    fn set_step(&mut self, step: &str) {
        info!("[MANAGER] Step: {}", step);
        self.step = Some(step.to_string());
        self.emit_current_status();
    }

    fn emit_current_status(&self) {
        if let Some(ref handle) = self.app_handle {
            let status = ConnectionStatus {
                state: self.state.clone(),
                transport: self.active.map(|t| t.as_str().to_string()),
                message: self.error_message.clone(),
                step: self.step.clone(),
            };
            info!(
                "[EVENT] emitting 'connection-status': state={:?} step={:?}",
                status.state, status.step
            );
            let _ = handle.emit("connection-status", status);
        }
    }

    pub fn status(&self) -> ConnectionStatus {
        ConnectionStatus {
            state: self.state.clone(),
            transport: self.active.map(|t| t.as_str().to_string()),
            message: self.error_message.clone(),
            step: self.step.clone(),
        }
    }

    pub async fn connect(&mut self) -> Result<ConnectionStatus, String> {
        info!("[MANAGER] === CONNECT REQUESTED ===");
        if self.state == ConnectionState::Connected {
            info!("[MANAGER] Already connected, returning current status");
            return Ok(self.status());
        }

        self.state = ConnectionState::Connecting;
        self.error_message = None;
        self.step = None;

        let step_cb = self.app_handle.clone().map(|h| {
            move |s: &str| {
                info!("[BLE PROGRESS] {}", s);
                let status = ConnectionStatus {
                    state: ConnectionState::Connecting,
                    transport: Some("BLE".to_string()),
                    message: None,
                    step: Some(s.to_string()),
                };
                let _ = h.emit("connection-status", status);
            }
        });

        if let Some(cb) = step_cb {
            self.ble.set_step_callback(cb);
        }

        let result = self.try_ble().await;
        info!("[MANAGER] connect() result: {:?}", result);
        result
    }

    async fn try_ble(&mut self) -> Result<ConnectionStatus, String> {
        info!("[MANAGER] Trying BLE transport...");
        self.set_step("Starting BLE scan");

        info!("[MANAGER] Calling ble.connect()...");
        self.ble.connect().await?;
        info!("[MANAGER] ble.connect() succeeded");

        self.set_step("Handshake: sending ping");
        info!("[MANAGER] Performing handshake...");
        perform_handshake(&mut self.ble).await?;
        self.set_step("Handshake: valid response received");
        info!("[MANAGER] Handshake succeeded");

        self.set_step("Synchronizing clock");
        let time_cmd = super::protocol::format_time_command();
        info!("[MANAGER] Sending time sync command: '{}'", time_cmd);
        match self.ble.send(&time_cmd).await {
            Ok(resp) => info!("[MANAGER] Time sync response: '{}'", resp.trim()),
            Err(e) => warn!("[MANAGER] Time sync failed (non-fatal): {}", e),
        }

        self.active = Some(TransportType::Ble);
        self.state = ConnectionState::Connected;
        self.set_step("Connected — fully operational");
        info!("[MANAGER] === CONNECTED VIA BLE ===");
        Ok(ConnectionStatus::connected("BLE").with_step("Connected"))
    }

    pub async fn disconnect(&mut self) -> Result<(), String> {
        info!("[MANAGER] === DISCONNECT REQUESTED ===");
        if let Some(transport_type) = self.active {
            match transport_type {
                TransportType::Ble => {
                    info!("[MANAGER] Disconnecting BLE...");
                    self.ble.disconnect().await?;
                }
                TransportType::Serial => {
                    info!("[MANAGER] Serial disconnect (no-op)");
                }
            }
        }
        self.active = None;
        self.state = ConnectionState::Disconnected;
        self.error_message = None;
        self.step = None;
        self.emit_current_status();
        info!("[MANAGER] Disconnected");
        Ok(())
    }

    pub async fn send_fire_forget(&mut self, command: &str) -> Result<(), String> {
        info!("[MANAGER] send_fire_forget: '{}'", command);
        match self.active {
            Some(TransportType::Ble) => self.ble.send(command).await.map(|_| ()),
            Some(TransportType::Serial) => {
                let msg = "Serial not available on iOS".to_string();
                error!("[MANAGER] {}", msg);
                Err(msg)
            }
            None => {
                let msg = "No active transport".to_string();
                warn!("[MANAGER] {}", msg);
                Err(msg)
            }
        }
    }

    pub async fn send_command(&mut self, command: &str) -> Result<String, String> {
        info!("[MANAGER] send_command: '{}'", command);
        match self.active {
            Some(TransportType::Ble) => {
                if !self.ble.is_connected() {
                    let msg = "BLE: not connected".to_string();
                    error!("[MANAGER] {}", msg);
                    return Err(msg);
                }
                self.ble.send(command).await
            }
            Some(TransportType::Serial) => {
                let msg = "Serial not available on iOS".to_string();
                error!("[MANAGER] {}", msg);
                Err(msg)
            }
            None => {
                let msg = "No active transport".to_string();
                warn!("[MANAGER] {}", msg);
                Err(msg)
            }
        }
    }

    pub fn is_connected(&self) -> bool {
        self.state == ConnectionState::Connected
    }
}
