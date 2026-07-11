pub const PING: &str = "ping";
pub const KORE_COMPANION: &str = "KORE_COMPANION";
pub const DELIMITER: char = '|';

pub fn format_command(cmd: &str, args: &[&str]) -> String {
    if args.is_empty() {
        cmd.to_string()
    } else {
        let mut result = cmd.to_string();
        for arg in args {
            result.push(DELIMITER);
            result.push_str(arg);
        }
        result
    }
}

pub fn is_valid_handshake(response: &str) -> bool {
    response.trim() == KORE_COMPANION
}
