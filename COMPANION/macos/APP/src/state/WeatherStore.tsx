import {
  createContext,
  useContext,
  useEffect,
  useMemo,
  useReducer,
  type ReactNode,
} from "react";
import { listen, type UnlistenFn } from "@tauri-apps/api/event";

interface WeatherData {
  temperature: number;
  max_temperature: number;
  min_temperature: number;
  weather_code: number;
}

interface WeatherStatusEvent {
  city: string | null;
  data: WeatherData | null;
  last_update: string | null;
}

interface WeatherState {
  city: string | null;
  data: WeatherData | null;
  last_update: string | null;
  loading: boolean;
  error: string | null;
}

type WeatherAction =
  | { type: "SET_WEATHER"; payload: WeatherStatusEvent }
  | { type: "SET_LOADING"; payload: boolean }
  | { type: "SET_ERROR"; payload: string | null };

const initialWeatherState: WeatherState = {
  city: null,
  data: null,
  last_update: null,
  loading: false,
  error: null,
};

function weatherReducer(
  state: WeatherState,
  action: WeatherAction,
): WeatherState {
  switch (action.type) {
    case "SET_WEATHER":
      return {
        ...state,
        city: action.payload.city,
        data: action.payload.data,
        last_update: action.payload.last_update,
        loading: false,
        error: null,
      };
    case "SET_LOADING":
      return { ...state, loading: action.payload };
    case "SET_ERROR":
      return { ...state, error: action.payload, loading: false };
    default:
      return state;
  }
}

interface WeatherContextValue {
  state: WeatherState;
  setLoading: (loading: boolean) => void;
  setError: (error: string | null) => void;
}

const WeatherContext = createContext<WeatherContextValue | null>(null);

function WeatherProvider({ children }: { children: ReactNode }) {
  const [state, dispatch] = useReducer(weatherReducer, initialWeatherState);

  useEffect(() => {
    let unlisten: UnlistenFn | undefined;

    async function setup() {
      unlisten = await listen<WeatherStatusEvent>("weather-status", (event) => {
        dispatch({ type: "SET_WEATHER", payload: event.payload });
      });
    }

    setup();

    return () => {
      if (unlisten) {
        unlisten();
      }
    };
  }, []);

  const value = useMemo<WeatherContextValue>(
    () => ({
      state,
      setLoading: (loading: boolean) =>
        dispatch({ type: "SET_LOADING", payload: loading }),
      setError: (error: string | null) =>
        dispatch({ type: "SET_ERROR", payload: error }),
    }),
    [state],
  );

  return (
    <WeatherContext.Provider value={value}>
      {children}
    </WeatherContext.Provider>
  );
}

function useWeather(): WeatherContextValue {
  const context = useContext(WeatherContext);
  if (!context) {
    throw new Error("useWeather must be used within a WeatherProvider");
  }
  return context;
}

export { WeatherProvider, useWeather };
