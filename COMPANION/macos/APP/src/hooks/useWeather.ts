import { useCallback, useEffect } from "react";
import { invoke } from "@tauri-apps/api/core";
import { useWeather } from "../state";

const CONFIG = {
  0: "Ensoleirado",
  1: "Parcialmente nublado",
  2: "Parcialmente nublado",
  3: "Parcialmente nublado",
  4: "Nublado",
  5: "Névoa",
  6: "Névoa",
  7: "Névoa",
  8: "Nublado",
  9: "Nublado",
  10: "Névoa",
  11: "Névoa",
  12: "Névoa",
  13: "Tempestade",
  14: "Tempestade",
  15: "Tempestade",
  16: "Tempestade",
  17: "Tempestade",
  18: "Tempestade",
  19: "Tempestade",
  20: "Névoa",
  21: "Névoa",
  22: "Névoa",
  23: "Névoa",
  24: "Nublado",
  25: "Nublado",
  26: "Nublado",
  27: "Nublado",
  28: "Nublado",
  29: "Nublado",
  30: "Névoa",
  31: "Névoa",
  32: "Ensoleirado",
  33: "Limpo",
  34: "Limpo",
  35: "Parcialmente nublado",
  36: "Limpo",
  37: "Névoa",
  38: "Névoa",
  39: "Névoa",
  40: "Névoa",
  41: "Névoa",
  42: "Névoa",
  43: "Névoa",
  44: "Névoa",
  45: "Névoa",
  46: "Névoa",
  47: "Névoa",
  48: "Névoa",
  49: "Chuva",
  50: "Chuva",
  51: "Chuva",
  52: "Chuva",
  53: "Chuva",
  54: "Chuva",
  55: "Chuva",
  56: "Chuva",
  57: "Chuva",
  58: "Chuva",
  59: "Chuva",
  60: "Chuva",
  61: "Chuva",
  62: "Chuva",
  63: "Chuva",
  64: "Chuva",
  65: "Chuva",
  66: "Chuva",
  67: "Chuva",
  68: "Neve",
  69: "Neve",
  70: "Neve",
  71: "Neve",
  72: "Neve",
  73: "Neve",
  74: "Neve",
  75: "Neve",
  76: "Neve",
  77: "Neve",
  78: "Tempestade",
  79: "Tempestade",
  80: "Tempestade",
  81: "Tempestade",
  82: "Tempestade",
  83: "Tempestade",
  84: "Tempestade",
  85: "Tempestade",
  86: "Tempestade",
  87: "Tempestade",
  88: "Tempestade",
  89: "Tempestade",
  90: "Tempestade",
  91: "Tempestade",
  92: "Tempestade",
  93: "Tempestade",
  94: "Tempestade",
  95: "Tempestade",
  96: "Tempestade",
  97: "Tempestade",
  98: "Tempestade",
  99: "Tempestade",
};

function weatherDescription(code: number): string {
  return CONFIG[code as keyof typeof CONFIG] ?? "Desconhecido";
}

export function useWeatherService() {
  const { state, setLoading, setError } = useWeather();
  const { data, city, last_update } = state;

  const condition = data ? weatherDescription(data.weather_code) : null;

  useEffect(() => {
    setLoading(true);
    invoke("weather_fetch")
      .catch((err) => setError(String(err)));
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);

  const fetch = useCallback(
    async (latitude?: number, longitude?: number, cityName?: string) => {
      setLoading(true);
      setError(null);
      try {
        await invoke("weather_fetch", {
          latitude: latitude ?? null,
          longitude: longitude ?? null,
          city: cityName ?? null,
        });
      } catch (err) {
        setError(String(err));
      }
    },
    [setLoading, setError],
  );

  const setLocation = useCallback(
    async (cityName: string, latitude: number, longitude: number) => {
      setLoading(true);
      setError(null);
      try {
        await invoke("weather_set_location", {
          city: cityName,
          latitude,
          longitude,
        });
      } catch (err) {
        setError(String(err));
      }
    },
    [setLoading, setError],
  );

  return {
    city,
    temperature: data?.temperature ?? null,
    maxTemperature: data?.max_temperature ?? null,
    minTemperature: data?.min_temperature ?? null,
    condition,
    code: data?.weather_code ?? null,
    lastUpdate: last_update,
    loading: state.loading,
    error: state.error,
    fetch,
    setLocation,
  };
}

export type { WeatherData } from "../state/WeatherStore";
