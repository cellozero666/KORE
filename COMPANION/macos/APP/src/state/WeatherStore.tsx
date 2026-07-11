import { createContext, useContext, useReducer, type ReactNode } from "react";

interface WeatherState {}

type WeatherAction = never;

const initialWeatherState: WeatherState = {};

function weatherReducer(
  state: WeatherState,
  _action: WeatherAction
): WeatherState {
  return state;
}

interface WeatherContextValue {
  state: WeatherState;
}

const WeatherContext = createContext<WeatherContextValue | null>(null);

function WeatherProvider({ children }: { children: ReactNode }) {
  const [state] = useReducer(weatherReducer, initialWeatherState);

  return (
    <WeatherContext.Provider value={{ state }}>
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
