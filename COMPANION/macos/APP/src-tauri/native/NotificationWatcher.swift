import Foundation
import AppKit
import ApplicationServices

private var observer: AXObserver?

@_silgen_name("emit_notification_ffi")
func emit_notification_ffi(
    _ app: UnsafePointer<CChar>,
    _ title: UnsafePointer<CChar>,
    _ body: UnsafePointer<CChar>
)

@_cdecl("check_accessibility_permission")
public func check_accessibility_permission() -> Bool {
    let options = [kAXTrustedCheckOptionPrompt.takeRetainedValue() as NSString: true]
    return AXIsProcessTrustedWithOptions(options as CFDictionary)
}

@_cdecl("is_notification_center_running")
public func is_notification_center_running() -> Bool {
    NSWorkspace.shared.runningApplications.contains {
        $0.bundleIdentifier == "com.apple.notificationcenterui"
    }
}

@_cdecl("start_notification_watcher_native")
public func start_notification_watcher_native() {
    guard let app = NSWorkspace.shared.runningApplications.first(
        where: { $0.bundleIdentifier == "com.apple.notificationcenterui" }
    ) else { return }

    let pid = app.processIdentifier
    var obs: AXObserver?
    let result = AXObserverCreate(pid, notificationCallbackHandler, &obs)

    guard result == .success, let obs else { return }

    let element = AXUIElementCreateApplication(pid)
    AXObserverAddNotification(obs, element, kAXCreatedNotification as CFString, nil)
    CFRunLoopAddSource(CFRunLoopGetMain(), AXObserverGetRunLoopSource(obs), .defaultMode)

    observer = obs
}

private func notificationCallbackHandler(
    _: AXObserver?,
    _ element: AXUIElement?,
    _ notification: CFString?,
    _: UnsafeMutableRawPointer?
) {
    guard let notification = notification as String?,
          notification == (kAXCreatedNotification as String),
          let element else { return }
    extractNotification(from: element)
}

private func extractNotification(from element: AXUIElement) {
    var description: CFTypeRef?
    let result = AXUIElementCopyAttributeValue(element, kAXDescriptionAttribute as CFString, &description)

    if result == .success, let text = description as? String {
        let parts = text.components(separatedBy: ", ")
        if parts.count >= 2 {
            let app = parts[0]
                .trimmingCharacters(in: .whitespacesAndNewlines)
                .replacingOccurrences(of: "\u{200E}", with: "")
            let title = parts[1]
            let body = parts.dropFirst(2).joined(separator: ", ")

            app.withCString { a in
                title.withCString { t in
                    body.withCString { b in
                        emit_notification_ffi(a, t, b)
                    }
                }
            }
            return
        }
    }

    var children: CFTypeRef?
    let childResult = AXUIElementCopyAttributeValue(element, kAXChildrenAttribute as CFString, &children)

    guard childResult == .success, let array = children as? [AXUIElement] else { return }
    for child in array { extractNotification(from: child) }
}
