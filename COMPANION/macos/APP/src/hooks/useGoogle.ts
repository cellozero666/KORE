import { useCallback } from "react";
import { invoke } from "@tauri-apps/api/core";
import { useGoogle } from "../state";

export function useGoogleService() {
  const { state, setLoading, setError } = useGoogle();

  const connect = useCallback(async () => {
    setLoading(true);
    setError(null);
    try {
      await invoke("google_connect");
    } catch (err) {
      setError(String(err));
    } finally {
      setLoading(false);
    }
  }, [setLoading, setError]);

  const disconnect = useCallback(async () => {
    setLoading(true);
    try {
      await invoke("google_disconnect");
    } catch (err) {
      setError(String(err));
    } finally {
      setLoading(false);
    }
  }, [setLoading, setError]);

  return {
    state,
    connect,
    disconnect,
  };
}
