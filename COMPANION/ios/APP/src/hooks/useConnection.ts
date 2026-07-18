import { useEffect, useCallback, useRef, useState } from "react";
import { invoke } from "@tauri-apps/api/core";
import { listen, type UnlistenFn } from "@tauri-apps/api/event";
import { useApp } from "../state";

interface ConnectionStatus {
  state: "Disconnected" | "Connecting" | "Pairing" | "Bonding" | "Connected" | "Error";
  transport: string | null;
  message: string | null;
  step: string | null;
}

export function useConnection() {
  const { setConnected, setLoading, setError } = useApp();
  const [connectionStep, setConnectionStep] = useState<string | null>(null);
  const pollingRef = useRef<ReturnType<typeof setInterval> | null>(null);
  const startTimeRef = useRef<number>(0);
  const [elapsed, setElapsed] = useState(0);
  const elapsedTimerRef = useRef<ReturnType<typeof setInterval> | null>(null);
  const isPollingRef = useRef(false);

  const startPolling = useCallback(() => {
    if (isPollingRef.current) return;
    isPollingRef.current = true;
    console.log("[DIAG] Starting step polling (every 1s)");

    pollingRef.current = setInterval(async () => {
      try {
        const status = await invoke<ConnectionStatus>(
          "get_connection_status",
        );
        console.log(
          `[DIAG] Poll: state=${status.state} step=${status.step} msg=${status.message}`,
        );
        setConnectionStep(status.step);
      } catch (err) {
        console.warn("[DIAG] Poll failed:", err);
      }
    }, 1000);
  }, []);

  const stopPolling = useCallback(() => {
    if (pollingRef.current) {
      clearInterval(pollingRef.current);
      pollingRef.current = null;
    }
    if (elapsedTimerRef.current) {
      clearInterval(elapsedTimerRef.current);
      elapsedTimerRef.current = null;
    }
    isPollingRef.current = false;
    setConnectionStep(null);
    setElapsed(0);
  }, []);

  const startConnection = useCallback(async () => {
    console.log("[DIAG] === START CONNECTION ===");
    setLoading(true);
    setError(null);
    setConnectionStep("Connecting...");
    startTimeRef.current = Date.now();
    startPolling();

    elapsedTimerRef.current = setInterval(() => {
      setElapsed(Math.floor((Date.now() - startTimeRef.current) / 1000));
    }, 1000);

    try {
      const result = await invoke<ConnectionStatus>("connect");
      console.log(
        `[DIAG] connect() returned: state=${result.state} step=${result.step} msg=${result.message}`,
      );
      switch (result.state) {
        case "Connected":
          console.log("[DIAG] ✅ Already connected on return");
          setConnected(true);
          setLoading(false);
          setError(null);
          stopPolling();
          break;
        case "Error":
          setError(result.message || "Conexão falhou");
          setLoading(false);
          stopPolling();
          break;
        default:
          // Connecting / Pairing / Bonding / Disconnected:
          // wait for event-based state transitions
          break;
      }
    } catch (err) {
      console.error("[DIAG] connect() threw:", err);
      setError(String(err));
      setLoading(false);
      stopPolling();
    }
  }, [setConnected, setLoading, setError, startPolling, stopPolling]);

  useEffect(() => {
    let unlisten: UnlistenFn | undefined;

    async function setup() {
      console.log("[DIAG] Setting up connection-status listener");
      unlisten = await listen<ConnectionStatus>(
        "connection-status",
        (event) => {
          const { state, message, step } = event.payload;
          console.log(
            `[DIAG] EVENT connection-status: state=${state} step=${step} msg=${message}`,
          );

          if (step) {
            setConnectionStep(step);
          }

          switch (state) {
            case "Connected":
              console.log("[DIAG] ✅ Connected event received");
              setConnected(true);
              setLoading(false);
              setError(null);
              stopPolling();
              break;
            case "Disconnected":
              console.log("[DIAG] Disconnected event received");
              setConnected(false);
              setLoading(false);
              stopPolling();
              break;
            case "Connecting":
              console.log("[DIAG] Connecting event received");
              setLoading(true);
              break;
            case "Pairing":
              console.log("[DIAG] 🔐 Pairing event received:", message);
              setLoading(true);
              break;
            case "Bonding":
              console.log("[DIAG] 🔗 Bonding event received");
              setLoading(true);
              break;
            case "Error":
              console.log("[DIAG] ❌ Error event received:", message);
              setConnected(false);
              setLoading(false);
              setError(message || "Erro de conexão");
              stopPolling();
              break;
          }
        },
      );

      await startConnection();
    }

    setup();

    return () => {
      console.log("[DIAG] Cleaning up connection hook");
      if (unlisten) {
        unlisten();
      }
      stopPolling();
    };
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);

  // --------------------------------------------------
  // Foreground detection — transparent reconnect
  // --------------------------------------------------
  // When the app returns from background (iOS suspends/resumes the WKWebView),
  // check if the BLE connection is still alive. If not, reconnect
  // without showing a permanent loading state.
  // --------------------------------------------------

  useEffect(() => {
    async function checkOnForeground() {
      console.log("[DIAG] App returned to foreground — checking connection");
      try {
        const status = await invoke<ConnectionStatus>(
          "get_connection_status",
        );
        console.log(
          `[DIAG] Foreground check: state=${status.state}`,
        );

        if (status.state === "Disconnected") {
          console.log("[DIAG] Reconnecting after foreground...");
          await startConnection();
        }
      } catch (err) {
        console.warn("[DIAG] Foreground check failed:", err);
      }
    }

    function handleVisibility() {
      if (!document.hidden) {
        checkOnForeground();
      }
    }

    function handleFocus() {
      checkOnForeground();
    }

    document.addEventListener("visibilitychange", handleVisibility);
    window.addEventListener("focus", handleFocus);

    return () => {
      document.removeEventListener("visibilitychange", handleVisibility);
      window.removeEventListener("focus", handleFocus);
    };
  }, [startConnection]);

  return { startConnection, connectionStep, elapsed };
}
