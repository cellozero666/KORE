import { useEffect } from "react";
import { invoke } from "@tauri-apps/api/core";
import { useWeather } from "../state";

// --------------------------------------------------
// WEATHER DESCRIPTION
// --------------------------------------------------

function weatherDescription(code: number): string {
  if (code === 0) {
    return "Sunny";
  }

  if (code <= 3) {
    return "Partly Cloudy";
  }

  if (code <= 48) {
    return "Cloudy";
  }

  if (code <= 67) {
    return "Rain";
  }

  if (code <= 77) {
    return "Snow";
  }

  return "Storm";
}

// --------------------------------------------------
// WEATHER ICON
// --------------------------------------------------

function weatherIcon(code: number): string {
  if (code === 0) {
    return "☀️";
  }

  if (code <= 3) {
    return "🌤️";
  }

  if (code <= 48) {
    return "☁️";
  }

  if (code <= 67) {
    return "🌧️";
  }

  if (code <= 77) {
    return "❄️";
  }

  return "⛈️";
}

// --------------------------------------------------
// WEATHER SERVICE
// --------------------------------------------------

export function useWeatherService() {
  const { state, setLoading, setError } = useWeather();

  const { data, city, last_update } = state;

  const condition = data
    ? weatherDescription(data.weather_code)
    : null;

  const icon = data
    ? weatherIcon(data.weather_code)
    : null;

  useEffect(() => {
    setLoading(true);

    invoke("weather_fetch")
      .catch((err) =>
        setError(String(err))
      );

    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);

  return {
    city,

    temperature:
      data?.temperature ?? null,

    maxTemperature:
      data?.max_temperature ?? null,

    minTemperature:
      data?.min_temperature ?? null,

    condition,

    icon,

    lastUpdate: last_update,

    loading: state.loading,

    error: state.error,
  };
}