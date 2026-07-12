fn main() {
    tauri_build::build();

    #[cfg(target_os = "macos")]
    {
        println!("cargo:rerun-if-changed=native/NotificationWatcher.swift");

        let status = std::process::Command::new("swiftc")
            .args([
                "-c",
                "native/NotificationWatcher.swift",
                "-o",
                "native/NotificationWatcher.o",
            ])
            .status()
            .expect("failed to run swiftc");

        assert!(status.success(), "Swift compilation failed");

        let status = std::process::Command::new("ar")
            .args([
                "rcs",
                "native/libnotification_watcher.a",
                "native/NotificationWatcher.o",
            ])
            .status()
            .expect("failed to run ar");

        assert!(status.success(), "ar failed");

        let dir = std::env::current_dir()
            .expect("current_dir failed")
            .join("native");

        println!("cargo:rustc-link-search=native={}", dir.display());
        println!("cargo:rustc-link-lib=static=notification_watcher");
        println!("cargo:rustc-link-lib=framework=ApplicationServices");
    }
}
