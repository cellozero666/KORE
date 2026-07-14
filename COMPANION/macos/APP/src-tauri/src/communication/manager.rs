use log::{error, info, warn};

use super::ble::BleTransport;
use super::handshake::{perform_handshake, Transport};
use super::serial::SerialTransport;
use super::types::TransportType;

use crate::models::connection::{ConnectionState, ConnectionStatus};

pub struct CommunicationManager {
    ble: BleTransport,
    serial: SerialTransport,
    active: Option<TransportType>,
    state: ConnectionState,
    error_message: Option<String>,
}

impl CommunicationManager {
    pub fn new() -> Self {
        CommunicationManager {
            ble: BleTransport::new(),
            serial: SerialTransport::new(),
            active: None,
            state: ConnectionState::Disconnected,
            error_message: None,
        }
    }

    pub fn status(&self) -> ConnectionStatus {
        ConnectionStatus {
            state: self.state.clone(),
            transport: self.active.map(|t| t.as_str().to_string()),
            message: self.error_message.clone(),
        }
    }

    pub async fn connect(&mut self) -> Result<ConnectionStatus, String> {
        if self.state == ConnectionState::Connected {
            return Ok(ConnectionStatus::connected(
                self.active.map(|t| t.as_str()).unwrap_or("Unknown"),
            ));
        }

        self.state = ConnectionState::Connecting;
        self.error_message = None;

        match self.try_ble().await {
            Ok(status) => {
                info!("BLE connected via {:?}", status.transport);
                Ok(status)
            }
            Err(ble_err) => {
                warn!("BLE failed: {}", ble_err);
                let _ = self.ble.disconnect().await;

                match self.try_serial().await {
                    Ok(status) => {
                        info!("Serial connected via {:?}", status.transport);
                        Ok(status)
                    }
                    Err(serial_err) => {
                        let msg = format!("BLE: {}. Serial: {}", ble_err, serial_err);
                        error!("All transports failed: {}", msg);
                        self.state = ConnectionState::Error;
                        self.active = None;
                        self.error_message = Some(msg.clone());
                        Err(msg)
                    }
                }
            }
        }
    }

    async fn try_ble(&mut self) -> Result<ConnectionStatus, String> {
        self.ble.connect().await?;
        perform_handshake(&mut self.ble).await?;

        let time_cmd = super::protocol::format_time_command();
        match self.ble.send(&time_cmd).await {
            Ok(resp) => info!("[TIME] initial sync: {}", resp.trim()),
            Err(e) => warn!("[TIME] initial sync via BLE failed: {}", e),
        }

        self.active = Some(TransportType::Ble);
        self.state = ConnectionState::Connected;
        Ok(ConnectionStatus::connected("BLE"))
    }

    async fn try_serial(&mut self) -> Result<ConnectionStatus, String> {
        self.serial.connect().await?;
        perform_handshake(&mut self.serial).await?;

        let time_cmd = super::protocol::format_time_command();
        match self.serial.send(&time_cmd).await {
            Ok(resp) => info!("[TIME] initial sync: {}", resp.trim()),
            Err(e) => warn!("[TIME] initial sync via Serial failed: {}", e),
        }

        self.active = Some(TransportType::Serial);
        self.state = ConnectionState::Connected;
        Ok(ConnectionStatus::connected("Serial"))
    }

    pub async fn disconnect(&mut self) -> Result<(), String> {
        if let Some(transport_type) = self.active {
            match transport_type {
                TransportType::Ble => self.ble.disconnect().await?,
                TransportType::Serial => self.serial.disconnect().await?,
            }
        }
        self.active = None;
        self.state = ConnectionState::Disconnected;
        self.error_message = None;
        Ok(())
    }

    /// Fire-and-forget: writes the command without waiting for a response.
    /// Used for notifications and other commands where the firmware does not reply.
    pub async fn send_fire_forget(&mut self, command: &str) -> Result<(), String> {
        match self.active {
            Some(TransportType::Ble) => self.ble.send_raw(command).await,
            Some(TransportType::Serial) => self.serial.send_raw(command).await,
            None => Err("No active transport".to_string()),
        }
    }

    pub async fn send_command(&mut self, command: &str) -> Result<String, String> {
        match self.active {
            Some(TransportType::Ble) => {
                if !self.ble.is_connected() {
                    return Err("BLE: not connected".to_string());
                }
                self.ble.send(command).await
            }
            Some(TransportType::Serial) => {
                if !self.serial.is_connected() {
                    return Err("Serial: not connected".to_string());
                }
                self.serial.send(command).await
            }
            None => Err("No active transport".to_string()),
        }
    }

    pub fn is_connected(&self) -> bool {
        self.state == ConnectionState::Connected
    }
}
