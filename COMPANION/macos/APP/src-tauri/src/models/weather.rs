use serde::{Deserialize, Serialize};

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct WeatherData {
    pub temperature: f64,
    pub max_temperature: f64,
    pub min_temperature: f64,
    pub weather_code: u16,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct WeatherStatus {
    pub city: Option<String>,
    pub data: Option<WeatherData>,
    pub last_update: Option<String>,
}

#[derive(Debug, Clone, Deserialize)]
pub struct IpInfoResponse {
    pub city: Option<String>,
    pub loc: Option<String>,
}

#[derive(Debug, Clone, Deserialize)]
pub struct OpenMeteoCurrent {
    pub temperature_2m: f64,
    pub weather_code: u16,
}

#[derive(Debug, Clone, Deserialize)]
pub struct OpenMeteoDaily {
    pub temperature_2m_max: Vec<f64>,
    pub temperature_2m_min: Vec<f64>,
}

#[derive(Debug, Clone, Deserialize)]
pub struct OpenMeteoResponse {
    pub current: OpenMeteoCurrent,
    pub daily: OpenMeteoDaily,
}
