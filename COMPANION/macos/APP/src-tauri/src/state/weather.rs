use crate::models::weather::WeatherData;
use tokio::sync::Mutex;

pub struct WeatherInternalState {
    pub city: Option<String>,
    pub latitude: Option<f64>,
    pub longitude: Option<f64>,
    pub data: Option<WeatherData>,
    pub last_payload: String,
    pub last_force_sync: u64,
    pub last_update: Option<String>,
}

impl WeatherInternalState {
    pub fn new() -> Self {
        WeatherInternalState {
            city: None,
            latitude: None,
            longitude: None,
            data: None,
            last_payload: String::new(),
            last_force_sync: 0,
            last_update: None,
        }
    }
}

pub struct WeatherState {
    pub inner: Mutex<WeatherInternalState>,
}

impl WeatherState {
    pub fn new() -> Self {
        WeatherState {
            inner: Mutex::new(WeatherInternalState::new()),
        }
    }
}
