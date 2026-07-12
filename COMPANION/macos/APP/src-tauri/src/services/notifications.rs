use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::OnceLock;
use log::{info, warn};
use tauri::Manager;
use tokio::sync::mpsc;

use crate::communication::protocol::format_command;

static WATCHER_STARTED: AtomicBool = AtomicBool::new(false);
static NOTIFICATION_TX: OnceLock<mpsc::UnboundedSender<String>> = OnceLock::new();

pub struct CapturedNotification {
    pub app: String,
    pub sender: String,
    pub content: String,
}

impl CapturedNotification {
    pub fn new(raw_app: &str, raw_title: &str, raw_body: &str) -> Self {
        let app = map_app(raw_app);
        let sender = if raw_title.is_empty() {
            app.clone()
        } else {
            raw_title.to_string()
        };
        let content = truncate(raw_body, 30);
        Self { app, sender, content }
    }

    pub fn to_protocol_string(&self) -> String {
        format_command("notification", &[&self.app, &self.sender, &self.content])
    }
}

fn map_app(raw: &str) -> String {
    match raw {
        "WhatsApp" => "whatsapp",
        "Calendar" | "Calendário" => "calendar",
        "Mail" | "Email" => "mail",
        "Messages" | "Mensagens" | "SMS" => "messages",
        _ => "settings",
    }
    .to_string()
}

fn truncate(s: &str, max: usize) -> String {
    let chars: Vec<char> = s.chars().collect();
    if chars.len() <= max {
        s.to_string()
    } else {
        let truncated: String = chars.iter().take(max).collect();
        format!("{}...", truncated)
    }
}

#[unsafe(no_mangle)]
pub extern "C" fn emit_notification_ffi(
    app: *const std::os::raw::c_char,
    title: *const std::os::raw::c_char,
    body: *const std::os::raw::c_char,
) {
    if app.is_null() || title.is_null() || body.is_null() {
        return;
    }

    let raw_app = unsafe { std::ffi::CStr::from_ptr(app) }
        .to_string_lossy()
        .into_owned();
    let raw_title = unsafe { std::ffi::CStr::from_ptr(title) }
        .to_string_lossy()
        .into_owned();
    let raw_body = unsafe { std::ffi::CStr::from_ptr(body) }
        .to_string_lossy()
        .into_owned();

    let notification = CapturedNotification::new(&raw_app, &raw_title, &raw_body);
    let protocol_msg = notification.to_protocol_string();

    info!(
        "[NOTIFICATION] captured: app={}, sender={}, content={}",
        notification.app, notification.sender, notification.content
    );

    if let Some(tx) = NOTIFICATION_TX.get() {
        if tx.send(protocol_msg).is_err() {
            warn!("[NOTIFICATION] channel closed");
        }
    }
}

pub async fn init(app_handle: tauri::AppHandle) {
    let permitted = check_accessibility();

    if !permitted {
        info!("[NOTIFICATIONS] Accessibility permission not granted");
        return;
    }

    if WATCHER_STARTED.swap(true, Ordering::SeqCst) {
        info!("[NOTIFICATIONS] watcher already running");
        return;
    }

    let (tx, mut rx) = mpsc::unbounded_channel::<String>();
    if NOTIFICATION_TX.set(tx).is_err() {
        warn!("[NOTIFICATIONS] channel already initialized");
        return;
    }

    let handle = app_handle.clone();
    tokio::spawn(async move {
        while let Some(msg) = rx.recv().await {
            let state = handle.state::<crate::state::connection::AppState>();
            info!("[NOTIFICATION] sending: {}", msg);

            // Calendar notifications require a small defer before BLE transmission.
            // This behavior was validated on macOS during HARNESS-008.
            // Other applications are sent immediately.
            if msg.starts_with("notification|calendar|") {
                tokio::time::sleep(std::time::Duration::from_millis(500)).await;
            }

            if let Err(e) = state.send_fire_forget(msg).await {
                warn!("[NOTIFICATION] send failed: {}", e);
            }
        }
    });

    if !is_notification_center_available() {
        info!("[NOTIFICATIONS] Notification Center not available");
        return;
    }

    unsafe {
        start_notification_watcher_native();
    }

    info!("[NOTIFICATIONS] watcher started");
}

fn check_accessibility() -> bool {
    #[cfg(target_os = "macos")]
    unsafe {
        check_accessibility_permission()
    }
    #[cfg(not(target_os = "macos"))]
    false
}

fn is_notification_center_available() -> bool {
    #[cfg(target_os = "macos")]
    unsafe {
        is_notification_center_running()
    }
    #[cfg(not(target_os = "macos"))]
    false
}

#[cfg(target_os = "macos")]
unsafe extern "C" {
    fn check_accessibility_permission() -> bool;
    fn is_notification_center_running() -> bool;
    fn start_notification_watcher_native();
}
