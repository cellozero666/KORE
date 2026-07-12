use std::time::Duration;

use async_trait::async_trait;
use btleplug::api::{Central, Manager as _, Peripheral as _, ScanFilter, WriteType};
use btleplug::platform::{Manager, Peripheral};
use futures::stream::StreamExt;
use log::{error, info, warn};
use tokio::sync::mpsc;
use uuid::Uuid;

use super::handshake::Transport;

const SERVICE_UUID_STR: &str = "8c0f0001-5a8f-4e7e-9d43-92d67e4d0001";
const RX_UUID_STR: &str = "8c0f0002-5a8f-4e7e-9d43-92d67e4d0001";
const TX_UUID_STR: &str = "8c0f0003-5a8f-4e7e-9d43-92d67e4d0001";

fn parse_uuid(s: &str) -> Result<Uuid, String> {
    Uuid::parse_str(s).map_err(|e| format!("invalid UUID '{}': {}", s, e))
}

pub struct BleTransport {
    peripheral: Option<Peripheral>,
    rx_char: Option<btleplug::api::Characteristic>,
    notification_rx: Option<mpsc::Receiver<String>>,
    connected: bool,
}

impl BleTransport {
    pub fn new() -> Self {
        BleTransport {
            peripheral: None,
            rx_char: None,
            notification_rx: None,
            connected: false,
        }
    }

    /// Write-only send — does not wait for a response notification.
    /// Used for fire-and-forget commands (e.g. notifications).
    pub async fn send_raw(&mut self, data: &str) -> Result<(), String> {
        let peripheral = self
            .peripheral
            .as_ref()
            .ok_or_else(|| "BLE: not connected".to_string())?;
        let rx_char = self
            .rx_char
            .as_ref()
            .ok_or_else(|| "BLE: RX characteristic not found".to_string())?;

        peripheral
            .write(rx_char, data.as_bytes(), WriteType::WithResponse)
            .await
            .map_err(|e| format!("BLE: write failed: {}", e))?;

        Ok(())
    }
}

#[async_trait]
impl Transport for BleTransport {
    async fn connect(&mut self) -> Result<(), String> {
        let service_uuid = parse_uuid(SERVICE_UUID_STR)?;
        let rx_uuid = parse_uuid(RX_UUID_STR)?;
        let tx_uuid = parse_uuid(TX_UUID_STR)?;

        let manager = Manager::new().await.map_err(|e| {
            let msg = format!("BLE: manager init failed: {}", e);
            error!("[BLE] {}", msg);
            msg
        })?;

        let adapters = manager.adapters().await.map_err(|e| {
            let msg = format!("BLE: adapter query failed: {}", e);
            error!("[BLE] {}", msg);
            msg
        })?;

        let adapter = adapters.into_iter().next().ok_or_else(|| {
            let msg = "BLE: no Bluetooth adapter found".to_string();
            warn!("[BLE] {}", msg);
            msg
        })?;

        adapter
            .start_scan(ScanFilter {
                services: vec![service_uuid],
            })
            .await
            .map_err(|e| {
                let msg = format!("BLE: scan start failed: {}", e);
                error!("[BLE] {}", msg);
                msg
            })?;

        let peripheral = match tokio::time::timeout(Duration::from_secs(10), async {
            loop {
                let peripherals = adapter.peripherals().await.map_err(|e| {
                    format!("BLE: peripheral query failed: {}", e)
                })?;
                if let Some(p) = peripherals.into_iter().next() {
                    return Ok::<_, String>(p);
                }
                tokio::time::sleep(Duration::from_millis(500)).await;
            }
        })
        .await
        {
            Ok(Ok(p)) => p,
            Ok(Err(e)) => {
                let _ = adapter.stop_scan().await;
                return Err(e);
            }
            Err(_) => {
                let _ = adapter.stop_scan().await;
                let msg = "BLE: no K.O.R.E. device found (scan timeout)".to_string();
                warn!("[BLE] {}", msg);
                return Err(msg);
            }
        };

        adapter.stop_scan().await.map_err(|e| {
            let msg = format!("BLE: stop scan failed: {}", e);
            error!("[BLE] {}", msg);
            msg
        })?;

        peripheral.connect().await.map_err(|e| {
            let msg = format!("BLE: connect failed: {}", e);
            error!("[BLE] {}", msg);
            msg
        })?;

        peripheral.discover_services().await.map_err(|e| {
            let msg = format!("BLE: service discovery failed: {}", e);
            error!("[BLE] {}", msg);
            msg
        })?;

        let characteristics = peripheral.characteristics();
        info!("[BLE] found {} characteristics", characteristics.len());

        let rx_char = characteristics
            .iter()
            .find(|c| c.uuid == rx_uuid)
            .cloned()
            .ok_or_else(|| {
                let msg = "BLE: RX characteristic not found".to_string();
                error!("[BLE] {}", msg);
                msg
            })?;

        let tx_char = characteristics
            .iter()
            .find(|c| c.uuid == tx_uuid)
            .cloned()
            .ok_or_else(|| {
                let msg = "BLE: TX characteristic not found".to_string();
                error!("[BLE] {}", msg);
                msg
            })?;

        let (notification_tx, notification_rx) = mpsc::channel::<String>(16);

        peripheral.subscribe(&tx_char).await.map_err(|e| {
            let msg = format!("BLE: subscribe to TX failed: {}", e);
            error!("[BLE] {}", msg);
            msg
        })?;

        let notify_peripheral = peripheral.clone();
        tokio::spawn(async move {
            match notify_peripheral.notifications().await {
                Ok(mut stream) => {
                    while let Some(data) = stream.next().await {
                        if let Ok(text) = String::from_utf8(data.value) {
                            let trimmed = text.trim().to_string();
                            info!("[BLE] notification received: '{}'", trimmed);
                            if notification_tx.send(trimmed).await.is_err() {
                                break;
                            }
                        }
                    }
                }
                Err(e) => {
                    error!("[BLE] failed to get notification stream: {}", e);
                }
            }
        });

        info!("[BLE] fully connected and ready");
        self.peripheral = Some(peripheral);
        self.rx_char = Some(rx_char);
        self.notification_rx = Some(notification_rx);
        self.connected = true;

        Ok(())
    }

    async fn disconnect(&mut self) -> Result<(), String> {
        if let Some(ref peripheral) = self.peripheral {
            peripheral.disconnect().await.map_err(|e| {
                let msg = format!("BLE: disconnect failed: {}", e);
                error!("[BLE] {}", msg);
                msg
            })?;
        }
        self.peripheral = None;
        self.rx_char = None;
        self.notification_rx = None;
        self.connected = false;
        Ok(())
    }

    async fn send(&mut self, data: &str) -> Result<String, String> {
        let peripheral = self
            .peripheral
            .as_ref()
            .ok_or_else(|| "BLE: not connected".to_string())?;
        let rx_char = self
            .rx_char
            .as_ref()
            .ok_or_else(|| "BLE: RX characteristic not found".to_string())?;
        let notification_rx = self
            .notification_rx
            .as_mut()
            .ok_or_else(|| "BLE: notification receiver not available".to_string())?;

        peripheral
            .write(rx_char, data.as_bytes(), WriteType::WithResponse)
            .await
            .map_err(|e| format!("BLE: write failed: {}", e))?;

        match tokio::time::timeout(Duration::from_secs(5), notification_rx.recv()).await {
            Ok(Some(response)) => {
                info!("[BLE] received response: '{}'", response);
                Ok(response)
            }
            Ok(None) => {
                let msg = "BLE: notification channel closed".to_string();
                error!("[BLE] {}", msg);
                Err(msg)
            }
            Err(_) => {
                let msg = "BLE: response timeout".to_string();
                warn!("[BLE] {}", msg);
                Err(msg)
            }
        }
    }

    fn is_connected(&self) -> bool {
        self.connected
    }

}
