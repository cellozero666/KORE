use serde::{Deserialize, Serialize};

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
pub enum ConnectionState {
    Disconnected,
    Connecting,
    Connected,
    Error,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct ConnectionStatus {
    pub state: ConnectionState,
    pub transport: Option<String>,
    pub message: Option<String>,
    pub step: Option<String>,
}

impl ConnectionStatus {
    pub fn disconnected() -> Self {
        Self {
            state: ConnectionState::Disconnected,
            transport: None,
            message: None,
            step: None,
        }
    }

    pub fn connecting(transport: &str) -> Self {
        Self {
            state: ConnectionState::Connecting,
            transport: Some(transport.to_string()),
            message: None,
            step: None,
        }
    }

    pub fn connected(transport: &str) -> Self {
        Self {
            state: ConnectionState::Connected,
            transport: Some(transport.to_string()),
            message: None,
            step: None,
        }
    }

    pub fn error(msg: &str) -> Self {
        Self {
            state: ConnectionState::Error,
            transport: None,
            message: Some(msg.to_string()),
            step: None,
        }
    }

    pub fn with_step(mut self, step: &str) -> Self {
        self.step = Some(step.to_string());
        self
    }
}
