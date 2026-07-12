import { useState, useRef, useCallback } from "react";
import { useDashboard } from "../hooks/useDashboard";
import { useSpotify, useGoogle } from "../state";
import "../assets/css/Dashboard.css";

function Dashboard() {
  const {
    firmwareVersion,
    firmwareVersionLoading,
    uptime,
    uptimeLoading,
    wifiStatus,
    wifiStatusLoading,
    connected,
    sendRawCommand,
  } = useDashboard();
  const { state: spotifyState } = useSpotify();
  const { state: googleState } = useGoogle();

  const inputRef = useRef<HTMLInputElement>(null);
  const [commandResponse, setCommandResponse] = useState<string | null>(null);
  const [commandError, setCommandError] = useState<string | null>(null);
  const [sending, setSending] = useState(false);

  const handleSend = useCallback(async () => {
    const cmd = inputRef.current?.value.trim();
    if (!cmd) return;

    setSending(true);
    setCommandResponse(null);
    setCommandError(null);

    try {
      const response = await sendRawCommand(cmd);
      setCommandResponse(response);
    } catch (err) {
      setCommandError(String(err));
    } finally {
      setSending(false);
    }
  }, [sendRawCommand]);

  const handleKeyDown = useCallback(
    (e: React.KeyboardEvent) => {
      if (e.key === "Enter") {
        handleSend();
      }
    },
    [handleSend],
  );

  return (
    <div className="dashboard">
      <header className="dashboard-header">
        <h1>K.O.R.E.</h1>
        <span
          className={`status-indicator ${connected ? "connected" : "disconnected"}`}
        />
        <span className="status-label">
          {connected ? "Connected" : "Disconnected"}
        </span>
      </header>

      <section className="dashboard-section">
        <div className="info-row">
          <span className="info-label">Firmware</span>
          <span className="info-value">
            {firmwareVersionLoading ? "..." : (firmwareVersion ?? "---")}
          </span>
        </div>
        <div className="info-row">
          <span className="info-label">Uptime</span>
          <span className="info-value">
            {uptimeLoading ? "..." : (uptime ?? "---")}
          </span>
        </div>
      </section>

      <div className="dashboard-divider" />

      <section className="dashboard-section">
        <div className="info-row">
          <span className="info-label">Spotify</span>
          <span
            className={`info-value ${spotifyState.connected ? "status-connected" : "status-disconnected"}`}
          >
            {spotifyState.connected ? "Connected" : "Disconnected"}
          </span>
        </div>
        <div className="info-row">
          <span className="info-label">Google</span>
          <span
            className={`info-value ${googleState.connected ? "status-connected" : "status-disconnected"}`}
          >
            {googleState.connected ? "Connected" : "Disconnected"}
          </span>
        </div>
      </section>

      <div className="dashboard-divider" />

      <section className="dashboard-section">
        <div className="info-row">
          <span className="info-label">Wi-Fi</span>
          <span
            className={`info-value ${
              wifiStatus?.connected ? "status-connected" : "status-disconnected"
            }`}
          >
            {wifiStatusLoading
              ? "..."
              : wifiStatus
                ? wifiStatus.connected
                  ? "Connected"
                  : "Disconnected"
                : "---"}
          </span>
        </div>
        <div className="info-row">
          <span className="info-label">IP</span>
          <span className="info-value">
            {wifiStatusLoading ? "..." : (wifiStatus?.ipAddress ?? "-")}
          </span>
        </div>
      </section>

      <div className="dashboard-divider" />

      <section className="dashboard-section command-test">
        <h3>Command Test</h3>
        <div className="command-input-row">
          <input
            ref={inputRef}
            type="text"
            placeholder="Digite um comando..."
            onKeyDown={handleKeyDown}
            disabled={!connected}
          />
          <button onClick={handleSend} disabled={sending || !connected}>
            {sending ? "..." : "Send"}
          </button>
        </div>
        {commandResponse !== null && (
          <div className="command-response">{commandResponse}</div>
        )}
        {commandError !== null && (
          <div className="command-response error">{commandError}</div>
        )}
      </section>
    </div>
  );
}

export default Dashboard;
