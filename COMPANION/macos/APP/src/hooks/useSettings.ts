import { useCallback, useEffect, useState } from "react";
import { invoke } from "@tauri-apps/api/core";
import { useSettings } from "../state";
import type { LocationConfig } from "../state/SettingsStore";

export interface CityOption {
  name: string;
  latitude: number;
  longitude: number;
  country: string;
  country_code: string;
}

export function useSettingsService() {
  const { state, setLocation, setLoading, setError } = useSettings();
  const [wifiSsid, setWifiSsid] = useState("");
  const [wifiPassword, setWifiPassword] = useState("");

  useEffect(() => {
    setLoading(true);
    invoke<LocationConfig>("settings_get")
      .then((config) => setLocation(config))
      .catch((err) => setError(String(err)));
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);

  const saveLocation = useCallback(
    async (config: LocationConfig) => {
      setLoading(true);
      setError(null);
      try {
        await invoke("settings_save_location", {
          autodetect: config.autodetect,
          country: config.country,
          city: config.city,
          latitude: config.latitude,
          longitude: config.longitude,
        });
      } catch (err) {
        setError(String(err));
      }
    },
    [setLoading, setError],
  );

  const searchCities = useCallback(
    async (query: string, countryCode: string): Promise<CityOption[]> => {
      try {
        return await invoke("settings_search_cities", {
          query,
          countryCode,
        });
      } catch (err) {
        setError(String(err));
        return [];
      }
    },
    [setError],
  );

  const connectWifi = useCallback(
    async (ssid: string, password: string) => {
      setLoading(true);
      setError(null);
      try {
        await invoke("settings_wifi_connect", { ssid, password });
        setWifiSsid("");
        setWifiPassword("");
      } catch (err) {
        setError(String(err));
      } finally {
        setLoading(false);
      }
    },
    [setLoading, setError],
  );

  return {
    location: state.location,
    loading: state.loading,
    error: state.error,
    wifiSsid,
    wifiPassword,
    setWifiSsid,
    setWifiPassword,
    saveLocation,
    searchCities,
    connectWifi,
  };
}

export type { LocationConfig } from "../state/SettingsStore";
