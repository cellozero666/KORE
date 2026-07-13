import { useEffect, useCallback } from "react";
import { invoke } from "@tauri-apps/api/core";
import { listen, type UnlistenFn } from "@tauri-apps/api/event";
import { useApp } from "../state";

interface ConnectionStatus {
  state: "Disconnected" | "Connecting" | "Connected" | "Error";
  transport: string | null;
  message: string | null;
}

export function useConnection() {
  const { setConnected, setLoading, setError } = useApp();

  const startConnection = useCallback(async () => {
    setLoading(true);
    setError(null);

    try {
      const result = await invoke<ConnectionStatus>("connect");
      if (result.state === "Error") {
        setError(result.message || "Conexão falhou");
        setLoading(false);
      }
    } catch (err) {
      setError(String(err));
      setLoading(false);
    }
  }, [setLoading, setError]);

  useEffect(() => {
    let unlisten: UnlistenFn | undefined;

    async function setup() {
      unlisten = await listen<ConnectionStatus>(
        "connection-status",
        (event) => {
          const { state, message } = event.payload;

          switch (state) {
            case "Connected":
              setConnected(true);
              setLoading(false);
              setError(null);
              break;
            case "Disconnected":
              setConnected(false);
              setLoading(false);
              break;
            case "Connecting":
              setLoading(true);
              break;
            case "Error":
              setConnected(false);
              setLoading(false);
              setError(message || "Erro de conexão");
              break;
          }
        },
      );

      await startConnection();
    }

    setup();

    return () => {
      if (unlisten) {
        unlisten();
      }
    };
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);

  return { startConnection };
}
