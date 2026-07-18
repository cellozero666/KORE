use async_trait::async_trait;

use super::handshake::Transport;

pub struct SerialTransport;

impl SerialTransport {
    pub fn new() -> Self {
        SerialTransport
    }

    pub async fn send_raw(&mut self, _data: &str) -> Result<(), String> {
        Err("Serial transport not available on iOS".to_string())
    }
}

#[async_trait]
impl Transport for SerialTransport {
    async fn connect(&mut self) -> Result<(), String> {
        Err("Serial transport not available on iOS".to_string())
    }

    async fn disconnect(&mut self) -> Result<(), String> {
        Ok(())
    }

    async fn send(&mut self, _data: &str) -> Result<String, String> {
        Err("Serial transport not available on iOS".to_string())
    }

    fn is_connected(&self) -> bool {
        false
    }
}
