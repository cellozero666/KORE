use crate::models::spotify::{SpotifyPlayback, SpotifyUser};
use tokio::sync::Mutex;

pub struct SpotifyInternalState {
    pub access_token: Option<String>,
    pub refresh_token: Option<String>,
    pub expires_at: u64,
    pub user: Option<SpotifyUser>,
    pub playback: Option<SpotifyPlayback>,
    pub connected: bool,
    pub code_verifier: Option<String>,
    pub auth_state: Option<String>,
    pub was_playing: bool,
}

impl SpotifyInternalState {
    pub fn new() -> Self {
        SpotifyInternalState {
            access_token: None,
            refresh_token: None,
            expires_at: 0,
            user: None,
            playback: None,
            connected: false,
            code_verifier: None,
            auth_state: None,
            was_playing: false,
        }
    }
}

pub struct SpotifyState {
    pub inner: Mutex<SpotifyInternalState>,
}

impl SpotifyState {
    pub fn new() -> Self {
        SpotifyState {
            inner: Mutex::new(SpotifyInternalState::new()),
        }
    }
}
