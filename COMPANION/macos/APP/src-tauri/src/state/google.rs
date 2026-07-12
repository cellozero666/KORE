use crate::models::google::GoogleUser;
use tokio::sync::Mutex;

pub struct GoogleInternalState {
    pub access_token: Option<String>,
    pub refresh_token: Option<String>,
    pub expires_at: u64,
    pub user: Option<GoogleUser>,
    pub connected: bool,
    pub last_email_id: String,
    pub last_calendar_check: String,
    pub code_verifier: Option<String>,
    pub auth_state: Option<String>,
}

impl GoogleInternalState {
    pub fn new() -> Self {
        GoogleInternalState {
            access_token: None,
            refresh_token: None,
            expires_at: 0,
            user: None,
            connected: false,
            last_email_id: String::new(),
            last_calendar_check: String::new(),
            code_verifier: None,
            auth_state: None,
        }
    }
}

pub struct GoogleState {
    pub inner: Mutex<GoogleInternalState>,
}

impl GoogleState {
    pub fn new() -> Self {
        GoogleState {
            inner: Mutex::new(GoogleInternalState::new()),
        }
    }
}
