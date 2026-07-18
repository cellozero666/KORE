#[derive(Debug, Clone, Copy, PartialEq)]
pub enum TransportType {
    Ble,
    Serial,
}

impl TransportType {
    pub fn as_str(&self) -> &'static str {
        match self {
            TransportType::Ble => "BLE",
            TransportType::Serial => "Serial",
        }
    }
}
