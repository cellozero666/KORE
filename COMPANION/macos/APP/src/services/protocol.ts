import { invoke } from "@tauri-apps/api/core";

export interface WifiStatus {
  connected: boolean;
  ipAddress: string | null;
}

function stripCommandPrefix(response: string, command: string): string {
  const prefix = `${command}|`;
  if (response.startsWith(prefix)) {
    return response.slice(prefix.length);
  }
  return response;
}

function formatUptime(seconds: number): string {
  const hours = Math.floor(seconds / 3600);
  const minutes = Math.floor((seconds % 3600) / 60);

  if (hours === 0) {
    return `${minutes} min`;
  }
  const paddedMinutes = minutes.toString().padStart(2, "0");
  return `${hours} h ${paddedMinutes} min`;
}

export async function getFirmwareVersion(): Promise<string> {
  const response = await invoke<string>("send_command", { command: "version" });
  return stripCommandPrefix(response.trim(), "version");
}

export async function getUptime(): Promise<string> {
  const response = await invoke<string>("send_command", { command: "uptime" });
  const cleaned = stripCommandPrefix(response.trim(), "uptime");
  const seconds = parseInt(cleaned, 10);
  return Number.isNaN(seconds) ? cleaned : formatUptime(seconds);
}

export async function getWifiStatus(): Promise<WifiStatus> {
  const response = await invoke<string>("send_command", { command: "wifi_status" });
  const cleaned = stripCommandPrefix(response.trim(), "wifi_status");
  const parts = cleaned.split("|");
  const isConnected = parts[0]?.toLowerCase() === "connected";
  const ipAddress = isConnected && parts.length > 1 ? parts[1] : null;
  return { connected: isConnected, ipAddress };
}

export async function sendCommand(command: string): Promise<string> {
  const response = await invoke<string>("send_command", { command });
  return response.trim();
}
