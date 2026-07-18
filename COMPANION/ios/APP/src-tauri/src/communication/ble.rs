use std::time::{Duration, Instant};

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
    step_callback: Option<Box<dyn Fn(&str) + Send + Sync>>,
}

impl BleTransport {
    pub fn new() -> Self {
        info!("[BLE] Created BleTransport instance");
        BleTransport {
            peripheral: None,
            rx_char: None,
            notification_rx: None,
            connected: false,
            step_callback: None,
        }
    }

    pub fn set_step_callback<F>(&mut self, callback: F)
    where
        F: Fn(&str) + Send + Sync + 'static,
    {
        self.step_callback = Some(Box::new(callback));
    }

    fn step(&self, msg: &str) {
        info!("[STEP] {}", msg);
        if let Some(ref cb) = self.step_callback {
            cb(msg);
        }
    }
}

#[async_trait]
impl Transport for BleTransport {
    async fn connect(&mut self) -> Result<(), String> {
        info!("[BLE] === CONNECT FLOW STARTED ===");
        let service_uuid = parse_uuid(SERVICE_UUID_STR)?;
        let rx_uuid = parse_uuid(RX_UUID_STR)?;
        let tx_uuid = parse_uuid(TX_UUID_STR)?;

        self.step("Initializing BLE manager");
        info!("[BLE] Step 1.0: Enter Manager::new()");
        let manager_start = Instant::now();
        let manager = Manager::new().await.map_err(|e| {
            let msg = format!("BLE: Manager::new() failed after {:?}: {}", manager_start.elapsed(), e);
            error!("[BLE] {}", msg);
            msg
        })?;
        info!("[BLE] Step 1.1: Manager::new() completed in {:?}", manager_start.elapsed());

        self.step("Querying BLE adapters");
        info!("[BLE] ======== ADAPTER INIT START ========");
        info!("[BLE] Step 2.0: About to call manager.adapters()");
        info!("[BLE] (This calls Adapter::new() -> run_corebluetooth_thread() -> CBCentralManager init)");
        let adapters_start = Instant::now();
        let adapters = match tokio::time::timeout(Duration::from_secs(10), manager.adapters()).await {
            Ok(Ok(adapters)) => {
                info!("[BLE] Step 2.1: manager.adapters() returned Ok with {} adapter(s) in {:?}",
                    adapters.len(), adapters_start.elapsed());
                adapters
            }
            Ok(Err(e)) => {
                let elapsed = adapters_start.elapsed();
                let msg = format!(
                    "BLE: adapter query failed after {:?}: {}",
                    elapsed, e
                );
                error!("[BLE] Step 2.ERR: {}", msg);
                self.step(&format!("Adapter error: {}", e));
                return Err(msg);
            }
            Err(_) => {
                let elapsed = adapters_start.elapsed();
                let msg = format!(
                    "BLE: adapter query TIMED OUT after {:?}. \
                     Cause: CBCentralManager delegate callback (centralManagerDidUpdateState:) \
                     never fired. Check Info.plist for NSBluetoothPeripheralUsageDescription \
                     and verify Bluetooth is enabled on device.",
                    elapsed
                );
                error!("[BLE] Step 2.TIMEOUT: {}", msg);
                self.step("Adapter query timed out — see logs");
                return Err(msg);
            }
        };
        info!("[BLE] ======== ADAPTER INIT END ========");

        info!("[BLE] Step 2.2: Selecting first adapter from {} found", adapters.len());
        let adapter = adapters.into_iter().next().ok_or_else(|| {
            let msg = "BLE: no Bluetooth adapter found (0 adapters returned)".to_string();
            warn!("[BLE] Step 2.ERR: {}", msg);
            self.step("No BLE adapter found");
            msg
        })?;
        info!("[BLE] Step 2.3: First adapter selected successfully");

        self.step("Starting BLE scan");
        info!("[BLE] Step 3: Starting BLE scan for service {}", SERVICE_UUID_STR);
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
        info!("[BLE] Scan started successfully, waiting for K.O.R.E. device (timeout: 10s)");

        self.step("Waiting for K.O.R.E. device");
        info!("[BLE] Step 4: Polling for peripherals...");
        let peripheral = match tokio::time::timeout(Duration::from_secs(10), async {
            let mut poll_count = 0;
            loop {
                poll_count += 1;
                let peripherals = adapter.peripherals().await.map_err(|e| {
                    format!("BLE: peripheral query failed: {}", e)
                })?;

                info!(
                    "[BLE] Scan poll #{}: {} device(s) found",
                    poll_count,
                    peripherals.len()
                );

                for (i, p) in peripherals.iter().enumerate() {
                    let name = p
                        .properties()
                        .await
                        .ok()
                        .flatten()
                        .and_then(|props| props.local_name)
                        .unwrap_or_else(|| "<unknown>".to_string());
                    let id = p.id();
                    info!(
                        "[BLE]   Device #{}: name='{}' id='{}'",
                        i + 1,
                        name,
                        id
                    );
                }

                if let Some(p) = peripherals.into_iter().next() {
                    let name = p
                        .properties()
                        .await
                        .ok()
                        .flatten()
                        .and_then(|props| props.local_name)
                        .unwrap_or_else(|| "<unknown>".to_string());
                    info!("[BLE] Selected first device: '{}'", name);
                    self.step(&format!("Device found: {}", name));
                    return Ok::<_, String>(p);
                }
                info!("[BLE] No devices yet, sleeping 500ms...");
                tokio::time::sleep(Duration::from_millis(500)).await;
            }
        })
        .await
        {
            Ok(Ok(p)) => {
                info!("[BLE] Device acquired successfully");
                p
            }
            Ok(Err(e)) => {
                info!("[BLE] Scan error, stopping scan");
                let _ = adapter.stop_scan().await;
                return Err(e);
            }
            Err(_) => {
                self.step("Scan timeout — no device found");
                info!("[BLE] Scan timeout reached (10s), stopping scan");
                let _ = adapter.stop_scan().await;
                let msg = "BLE: no K.O.R.E. device found (scan timeout)".to_string();
                warn!("[BLE] {}", msg);
                return Err(msg);
            }
        };

        self.step("Stopping BLE scan");
        info!("[BLE] Step 5: Stopping BLE scan");
        adapter.stop_scan().await.map_err(|e| {
            let msg = format!("BLE: stop scan failed: {}", e);
            error!("[BLE] {}", msg);
            msg
        })?;
        info!("[BLE] Scan stopped");

        self.step("Connecting to device");
        info!("[BLE] Step 6: Connecting to peripheral...");
        info!("[BLE] Peripheral ID: {:?}", peripheral.id());
        peripheral.connect().await.map_err(|e| {
            let msg = format!("BLE: connect failed: {}", e);
            error!("[BLE] {}", msg);
            msg
        })?;
        info!("[BLE] Connection established");

        self.step("Discovering services");
        info!("[BLE] Step 7: Discovering services...");
        peripheral.discover_services().await.map_err(|e| {
            let msg = format!("BLE: service discovery failed: {}", e);
            error!("[BLE] {}", msg);
            msg
        })?;
        info!("[BLE] Service discovery complete");

        self.step("Discovering characteristics");
        info!("[BLE] Step 8: Querying characteristics...");
        let characteristics = peripheral.characteristics();
        info!(
            "[BLE] Found {} characteristic(s) for service {}",
            characteristics.len(),
            SERVICE_UUID_STR
        );
        for (i, c) in characteristics.iter().enumerate() {
            info!(
                "[BLE]   Char #{}: uuid='{}' properties='{:?}'",
                i + 1,
                c.uuid,
                c.properties
            );
        }

        let rx_char = characteristics
            .iter()
            .find(|c| c.uuid == rx_uuid)
            .cloned()
            .ok_or_else(|| {
                let msg = format!(
                    "BLE: RX characteristic '{}' not found",
                    RX_UUID_STR
                );
                error!("[BLE] {}", msg);
                msg
            })?;
        info!("[BLE] RX characteristic found: uuid={}", rx_char.uuid);

        let tx_char = characteristics
            .iter()
            .find(|c| c.uuid == tx_uuid)
            .cloned()
            .ok_or_else(|| {
                let msg = format!(
                    "BLE: TX characteristic '{}' not found",
                    TX_UUID_STR
                );
                error!("[BLE] {}", msg);
                msg
            })?;
        info!("[BLE] TX characteristic found: uuid={}", tx_char.uuid);

        let (notification_tx, notification_rx) = mpsc::channel::<String>(16);

        self.step("Subscribing to notifications");
        info!("[BLE] Step 9: Subscribing to TX notifications...");
        peripheral.subscribe(&tx_char).await.map_err(|e| {
            let msg = format!("BLE: subscribe to TX failed: {}", e);
            error!("[BLE] {}", msg);
            msg
        })?;
        info!("[BLE] Subscribed to TX notifications");

        info!("[BLE] Step 10: Spawning notification listener");
        let notify_peripheral = peripheral.clone();
        tokio::spawn(async move {
            info!("[BLE] Notification listener started");
            match notify_peripheral.notifications().await {
                Ok(mut stream) => {
                    info!("[BLE] Notification stream acquired");
                    while let Some(data) = stream.next().await {
                        if let Ok(text) = String::from_utf8(data.value) {
                            let trimmed = text.trim().to_string();
                            info!("[BLE] Notification received: '{}'", trimmed);
                            if notification_tx.send(trimmed).await.is_err() {
                                info!("[BLE] Notification receiver dropped, stopping listener");
                                break;
                            }
                        } else {
                            warn!(
                                "[BLE] Received non-UTF8 notification data"
                            );
                        }
                    }
                }
                Err(e) => {
                    error!("[BLE] failed to get notification stream: {}", e);
                }
            }
            info!("[BLE] Notification listener terminated");
        });

        info!("[BLE] === CONNECT FLOW COMPLETE ===");
        self.step("Connected — ready");
        self.peripheral = Some(peripheral);
        self.rx_char = Some(rx_char);
        self.notification_rx = Some(notification_rx);
        self.connected = true;

        Ok(())
    }

    async fn disconnect(&mut self) -> Result<(), String> {
        info!("[BLE] === DISCONNECT ===");
        if let Some(ref peripheral) = self.peripheral {
            info!("[BLE] Disconnecting from peripheral...");
            peripheral.disconnect().await.map_err(|e| {
                let msg = format!("BLE: disconnect failed: {}", e);
                error!("[BLE] {}", msg);
                msg
            })?;
            info!("[BLE] Disconnected successfully");
        }
        self.peripheral = None;
        self.rx_char = None;
        self.notification_rx = None;
        self.connected = false;
        info!("[BLE] BleTransport state reset");
        Ok(())
    }

    async fn send(&mut self, data: &str) -> Result<String, String> {
        self.send_with_timeout(data, 5).await
    }

    fn is_connected(&self) -> bool {
        let status = self.connected;
        info!("[BLE] is_connected() = {}", status);
        status
    }
}

// --------------------------------------------------
// BleTransport-specific methods
// --------------------------------------------------

impl BleTransport {
    async fn send_with_timeout(
        &mut self,
        data: &str,
        timeout_secs: u64,
    ) -> Result<String, String> {
        info!("[BLE] SEND (timeout={}s): '{}'", timeout_secs, data);
        let peripheral = self
            .peripheral
            .as_ref()
            .ok_or_else(|| {
                let msg = "BLE: not connected".to_string();
                error!("[BLE] {}", msg);
                msg
            })?;
        let rx_char = self
            .rx_char
            .as_ref()
            .ok_or_else(|| {
                let msg = "BLE: RX characteristic not found".to_string();
                error!("[BLE] {}", msg);
                msg
            })?;
        let notification_rx = self
            .notification_rx
            .as_mut()
            .ok_or_else(|| {
                let msg = "BLE: notification receiver not available".to_string();
                error!("[BLE] {}", msg);
                msg
            })?;

        info!("[BLE] Writing to RX characteristic...");
        peripheral
            .write(rx_char, data.as_bytes(), WriteType::WithResponse)
            .await
            .map_err(|e| {
                let msg = format!("BLE: write failed: {}", e);
                error!("[BLE] {}", msg);
                msg
            })?;
        info!(
            "[BLE] Write successful, waiting for response (timeout: {}s)",
            timeout_secs
        );

        match tokio::time::timeout(
            Duration::from_secs(timeout_secs),
            notification_rx.recv(),
        )
        .await
        {
            Ok(Some(response)) => {
                info!("[BLE] Response received: '{}'", response);
                Ok(response)
            }
            Ok(None) => {
                let msg = "BLE: notification channel closed".to_string();
                error!("[BLE] {}", msg);
                Err(msg)
            }
            Err(_) => {
                let msg = format!("BLE: response timeout ({}s)", timeout_secs);
                warn!("[BLE] {}", msg);
                Err(msg)
            }
        }
    }

    pub async fn send_pairing_trigger(&mut self) -> Result<String, String> {
        self.step("Initiating secure pairing — iOS dialog may appear");
        info!("[BLE] Initiating pairing trigger (timeout: 20s)");

        let result = self.send_with_timeout(super::protocol::PING, 20).await;

        match &result {
            Ok(response) => info!("[BLE] Pairing trigger completed: '{}'", response.trim()),
            Err(e) => {
                warn!("[BLE] Pairing trigger failed: {}", e);
                self.step(&format!("Pairing failed: {}", e));
            }
        }

        result
    }
}
