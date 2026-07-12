import { useState, useCallback } from "react";
import { invoke } from "@tauri-apps/api/core";
import { useGoogle } from "../state";

interface GmailCheckResult {
  timestamp: string;
  endpoint: string;
  query: string;
  messages_found: number;
  message_ids: string[];
  messages: Array<{ id: string; from: string; subject: string }>;
  payloads: string[];
  send_fire_forget_called: boolean;
  peripheral_write_result: string;
  error: string | null;
}

export function useGoogleService() {
  const { state, setLoading, setError } = useGoogle();
  const [diagResult, setDiagResult] = useState<GmailCheckResult | null>(null);
  const [diagLoading, setDiagLoading] = useState(false);

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

  const checkMail = useCallback(async () => {
    setDiagLoading(true);
    setDiagResult(null);
    try {
      const result = await invoke<GmailCheckResult>("gmail_check_diagnostic");
      setDiagResult(result);
    } catch (err) {
      setError(String(err));
    } finally {
      setDiagLoading(false);
    }
  }, []);

  return {
    state,
    connect,
    disconnect,
    checkMail,
    diagResult,
    diagLoading,
  };
}
