fn main() {
    tauri_build::build();

    // iOS needs explicit CoreBluetooth.framework link for btleplug
    if std::env::var("CARGO_CFG_TARGET_OS").unwrap() == "ios" {
        println!("cargo:rustc-link-lib=framework=CoreBluetooth");
    }
}
