import { useEffect, useCallback, useRef, useState } from "react";
import { invoke } from "@tauri-apps/api/core";
import { listen, type UnlistenFn } from "@tauri-apps/api/event";
import { useApp } from "../state";

interface ConnectionStatus {
  state: "Disconnected" | "Connecting" | "Connected" | "Error";
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
      if (result.state === "Error") {
        setError(result.message || "Conexão falhou");
        setLoading(false);
        stopPolling();
      }
    } catch (err) {
      console.error("[DIAG] connect() threw:", err);
      setError(String(err));
      setLoading(false);
      stopPolling();
    }
  }, [setLoading, setError, startPolling, stopPolling]);

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

  return { startConnection, connectionStep, elapsed };
}
