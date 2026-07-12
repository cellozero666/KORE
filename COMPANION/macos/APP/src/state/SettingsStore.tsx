import {
  createContext,
  useContext,
  useEffect,
  useMemo,
  useReducer,
  type ReactNode,
} from "react";
import { listen, type UnlistenFn } from "@tauri-apps/api/event";

export interface LocationConfig {
  autodetect: boolean;
  country: string;
  city: string;
  latitude: number;
  longitude: number;
}

interface SettingsState {
  location: LocationConfig | null;
  loading: boolean;
  error: string | null;
}

type SettingsAction =
  | { type: "SET_LOCATION"; payload: LocationConfig }
  | { type: "SET_LOADING"; payload: boolean }
  | { type: "SET_ERROR"; payload: string | null };

const initialSettingsState: SettingsState = {
  location: null,
  loading: false,
  error: null,
};

function settingsReducer(
  state: SettingsState,
  action: SettingsAction,
): SettingsState {
  switch (action.type) {
    case "SET_LOCATION":
      return { ...state, location: action.payload, loading: false, error: null };
    case "SET_LOADING":
      return { ...state, loading: action.payload };
    case "SET_ERROR":
      return { ...state, error: action.payload, loading: false };
    default:
      return state;
  }
}

interface SettingsContextValue {
  state: SettingsState;
  setLocation: (config: LocationConfig) => void;
  setLoading: (loading: boolean) => void;
  setError: (error: string | null) => void;
}

const SettingsContext = createContext<SettingsContextValue | null>(null);

function SettingsProvider({ children }: { children: ReactNode }) {
  const [state, dispatch] = useReducer(settingsReducer, initialSettingsState);

  useEffect(() => {
    let unlisten: UnlistenFn | undefined;

    async function setup() {
      unlisten = await listen<LocationConfig>("settings-updated", (event) => {
        dispatch({ type: "SET_LOCATION", payload: event.payload });
      });
    }

    setup();

    return () => {
      if (unlisten) {
        unlisten();
      }
    };
  }, []);

  const value = useMemo<SettingsContextValue>(
    () => ({
      state,
      setLocation: (config: LocationConfig) =>
        dispatch({ type: "SET_LOCATION", payload: config }),
      setLoading: (loading: boolean) =>
        dispatch({ type: "SET_LOADING", payload: loading }),
      setError: (error: string | null) =>
        dispatch({ type: "SET_ERROR", payload: error }),
    }),
    [state],
  );

  return (
    <SettingsContext.Provider value={value}>
      {children}
    </SettingsContext.Provider>
  );
}

function useSettings(): SettingsContextValue {
  const context = useContext(SettingsContext);
  if (!context) {
    throw new Error("useSettings must be used within a SettingsProvider");
  }
  return context;
}

export { SettingsProvider, useSettings };
