use serde::{Deserialize, Serialize};

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct LocationConfig {
    pub autodetect: bool,
    pub country: String,
    pub city: String,
    pub latitude: f64,
    pub longitude: f64,
}

impl Default for LocationConfig {
    fn default() -> Self {
        LocationConfig {
            autodetect: true,
            country: String::new(),
            city: String::new(),
            latitude: 0.0,
            longitude: 0.0,
        }
    }
}

#[derive(Debug, Clone, Default, Serialize, Deserialize)]
pub struct SettingsConfig {
    pub location: LocationConfig,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct CityResult {
    pub name: String,
    pub latitude: f64,
    pub longitude: f64,
    pub country: String,
    pub country_code: String,
}

#[derive(Debug, Clone, Deserialize)]
pub(crate) struct GeocodingResult {
    pub name: String,
    pub latitude: f64,
    pub longitude: f64,
    pub country: String,
    pub country_code: String,
}

#[derive(Debug, Clone, Deserialize)]
pub(crate) struct GeocodingResponse {
    pub results: Option<Vec<GeocodingResult>>,
}
