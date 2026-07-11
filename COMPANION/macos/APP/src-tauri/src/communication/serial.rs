use std::io::{Read, Write};
use std::time::Duration;

use async_trait::async_trait;
use log::{error, info, warn};
use serialport::SerialPort;
use tokio::sync::Mutex;

use super::handshake::Transport;

/// macOS internal ports that should be ignored during auto-detection.
const IGNORED_PORT_PREFIXES: &[&str] = &[
    "cu.debug-console",
    "tty.debug-console",
    "cu.Bluetooth-Incoming-Port",
    "tty.Bluetooth-Incoming-Port",
    "cu.Bluetooth",
    "tty.Bluetooth",
    "cu.iPhone",
    "tty.iPhone",
    "cu.wlan-debug",
    "tty.wlan-debug",
];

fn should_ignore(port_name: &str) -> bool {
    let name = port_name.trim();
    for prefix in IGNORED_PORT_PREFIXES {
        if name.contains(prefix) {
            return true;
        }
    }
    false
}

pub struct SerialTransport {
    port: Option<Mutex<Box<dyn SerialPort>>>,
    connected: bool,
}

impl SerialTransport {
    pub fn new() -> Self {
        SerialTransport {
            port: None,
            connected: false,
        }
    }
}

#[async_trait]
impl Transport for SerialTransport {
    async fn connect(&mut self) -> Result<(), String> {
        let ports = serialport::available_ports().map_err(|e| {
            let msg = format!("Serial: port enumeration failed: {}", e);
            error!("[SERIAL] {}", msg);
            msg
        })?;

        let candidates: Vec<_> = ports
            .iter()
            .filter(|p| !should_ignore(&p.port_name))
            .collect();

        if candidates.is_empty() {
            let msg = "Serial: no suitable port found (all filtered out)".to_string();
            warn!("[SERIAL] {}", msg);
            return Err(msg);
        }

        for port_info in &candidates {
            let port_name = &port_info.port_name;

            match serialport::new(port_name, 115_200)
                .timeout(Duration::from_millis(1000))
                .open()
            {
                Ok(mut port) => {
                    let cmd = b"ping\n";
                    if let Err(e) = port.write_all(cmd) {
                        warn!("[SERIAL] write to '{}' failed: {}", port_name, e);
                        continue;
                    }

                    let mut buf = [0u8; 256];
                    match port.read(&mut buf) {
                        Ok(size) => {
                            let response = String::from_utf8_lossy(&buf[..size])
                                .trim()
                                .to_string();

                            if response.contains("KORE_COMPANION") {
                                info!("[SERIAL] K.O.R.E. found on '{}'!", port_name);
                                self.port = Some(Mutex::new(port));
                                self.connected = true;
                                return Ok(());
                            }
                        }
                        Err(e) => {
                            warn!("[SERIAL] read from '{}' failed: {}", port_name, e);
                            continue;
                        }
                    }
                }
                Err(e) => {
                    warn!("[SERIAL] failed to open '{}': {}", port_name, e);
                    continue;
                }
            }
        }

        let msg = "Serial: K.O.R.E. device not found on any port".to_string();
        error!("[SERIAL] {}", msg);
        Err(msg)
    }

    async fn disconnect(&mut self) -> Result<(), String> {
        self.port = None;
        self.connected = false;
        Ok(())
    }

    async fn send(&mut self, data: &str) -> Result<String, String> {
        let mutex = self
            .port
            .as_ref()
            .ok_or_else(|| "Serial: not connected".to_string())?;

        let mut port = mutex.lock().await;
        let cmd = format!("{}\n", data);
        port.write_all(cmd.as_bytes())
            .map_err(|e| format!("Serial: write error: {}", e))?;

        let mut buf = [0u8; 1024];
        let n = port
            .read(&mut buf)
            .map_err(|e| format!("Serial: read error: {}", e))?;

        let response = String::from_utf8_lossy(&buf[..n]).trim().to_string();
        info!("[SERIAL] received: '{}'", response);

        Ok(response)
    }

    fn is_connected(&self) -> bool {
        self.connected
    }

    fn transport_type(&self) -> &'static str {
        "Serial"
    }
}
