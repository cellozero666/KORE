use serde::{Deserialize, Serialize};

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct GoogleUser {
    pub id: String,
    pub display_name: String,
    pub email: String,
    pub image_url: Option<String>,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct GoogleStatus {
    pub connected: bool,
    pub user: Option<GoogleUser>,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct GoogleTokenFile {
    pub refresh_token: String,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct GoogleTokenResponse {
    pub access_token: String,
    pub expires_in: u64,
    pub scope: String,
    pub token_type: String,
    pub refresh_token: Option<String>,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct GmailMessage {
    pub id: String,
}

#[derive(Debug, Clone, Deserialize)]
pub struct GmailListResponse {
    pub messages: Option<Vec<GmailMessage>>,
}

#[derive(Debug, Clone, Deserialize)]
pub struct GmailMessagePart {
    pub name: String,
    pub value: String,
}

#[derive(Debug, Clone, Deserialize)]
pub struct GmailMessagePayload {
    pub headers: Vec<GmailMessagePart>,
}

#[derive(Debug, Clone, Deserialize)]
pub struct GmailMessageResponse {
    pub payload: GmailMessagePayload,
}

#[derive(Debug, Clone, Deserialize)]
pub struct CalendarEvent {
    pub summary: Option<String>,
    pub organizer: Option<CalendarOrganizer>,
}

#[derive(Debug, Clone, Deserialize)]
pub struct CalendarOrganizer {
    pub display_name: Option<String>,
}

#[derive(Debug, Clone, Deserialize)]
pub struct CalendarListResponse {
    pub items: Option<Vec<CalendarEvent>>,
}

#[derive(Debug, Clone, Deserialize)]
pub struct GoogleProfile {
    pub id: String,
    pub name: Option<String>,
    pub email: Option<String>,
    pub picture: Option<String>,
}


