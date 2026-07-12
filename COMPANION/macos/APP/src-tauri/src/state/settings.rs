use crate::models::settings::LocationConfig;
use tokio::sync::Mutex;

pub struct SettingsInternalState {
    pub location_config: LocationConfig,
}

impl SettingsInternalState {
    pub fn new() -> Self {
        SettingsInternalState {
            location_config: LocationConfig::default(),
        }
    }
}

pub struct SettingsState {
    pub inner: Mutex<SettingsInternalState>,
}

impl SettingsState {
    pub fn new() -> Self {
        SettingsState {
            inner: Mutex::new(SettingsInternalState::new()),
        }
    }
}
