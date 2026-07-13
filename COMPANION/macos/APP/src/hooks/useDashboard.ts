import { useEffect, useCallback } from "react";
import { useApp } from "../state";
import { useDashboardStore } from "../state";
import {
  getFirmwareVersion,
  getUptime,
  getWifiStatus,
  sendCommand,
} from "../services/protocol";

export function useDashboard() {
  const { state: appState } = useApp();
  const {
    state: dashboardState,
    setFirmwareVersion,
    setFirmwareVersionLoading,
    setUptime,
    setUptimeLoading,
    setWifiStatus,
    setWifiStatusLoading,
  } = useDashboardStore();

  const refresh = useCallback(async () => {
    setFirmwareVersionLoading(true);
    setUptimeLoading(true);
    setWifiStatusLoading(true);

    try {
      const version = await getFirmwareVersion();
      setFirmwareVersion(version);
    } catch {
      setFirmwareVersionLoading(false);
    }

    try {
      const uptime = await getUptime();
      setUptime(uptime);
    } catch {
      setUptimeLoading(false);
    }

    try {
      const status = await getWifiStatus();
      setWifiStatus(status);
    } catch {
      setWifiStatusLoading(false);
    }
  }, [
    setFirmwareVersion,
    setFirmwareVersionLoading,
    setUptime,
    setUptimeLoading,
    setWifiStatus,
    setWifiStatusLoading,
  ]);

  useEffect(() => {
    if (appState.connected) {
      refresh();
    }
  }, [appState.connected, refresh]);

  const sendRawCommand = useCallback(
    async (command: string): Promise<string> => {
      return await sendCommand(command);
    },
    [],
  );

  return {
    firmwareVersion: dashboardState.firmwareVersion,
    firmwareVersionLoading: dashboardState.firmwareVersionLoading,
    uptime: dashboardState.uptime,
    uptimeLoading: dashboardState.uptimeLoading,
    wifiStatus: dashboardState.wifiStatus,
    wifiStatusLoading: dashboardState.wifiStatusLoading,
    connected: appState.connected,
    sendRawCommand,
  };
}
