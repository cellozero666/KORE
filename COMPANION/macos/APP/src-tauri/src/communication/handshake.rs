use async_trait::async_trait;

use super::protocol;

#[async_trait]
pub trait Transport: Send + Sync {
    async fn connect(&mut self) -> Result<(), String>;
    async fn disconnect(&mut self) -> Result<(), String>;
    async fn send(&mut self, data: &str) -> Result<String, String>;
    fn is_connected(&self) -> bool;
    fn transport_type(&self) -> &'static str;
}

pub async fn perform_handshake(transport: &mut dyn Transport) -> Result<(), String> {
    let response = transport.send(protocol::PING).await?;
    if protocol::is_valid_handshake(&response) {
        Ok(())
    } else {
        Err(format!(
            "Handshake failed: unexpected response '{}'",
            response.trim()
        ))
    }
}
