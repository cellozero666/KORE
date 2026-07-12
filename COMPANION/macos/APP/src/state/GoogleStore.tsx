import {
  createContext,
  useContext,
  useEffect,
  useMemo,
  useReducer,
  type ReactNode,
} from "react";
import { listen, type UnlistenFn } from "@tauri-apps/api/event";

interface GoogleUser {
  id: string;
  display_name: string;
  email: string;
  image_url: string | null;
}

interface GoogleStatusEvent {
  connected: boolean;
  user: GoogleUser | null;
}

interface GoogleState {
  connected: boolean;
  user: GoogleUser | null;
  loading: boolean;
  error: string | null;
}

type GoogleAction =
  | { type: "SET_CONNECTED"; payload: boolean }
  | { type: "SET_USER"; payload: GoogleUser | null }
  | { type: "SET_LOADING"; payload: boolean }
  | { type: "SET_ERROR"; payload: string | null };

const initialGoogleState: GoogleState = {
  connected: false,
  user: null,
  loading: false,
  error: null,
};

function googleReducer(
  state: GoogleState,
  action: GoogleAction,
): GoogleState {
  switch (action.type) {
    case "SET_CONNECTED":
      return { ...state, connected: action.payload };
    case "SET_USER":
      return { ...state, user: action.payload };
    case "SET_LOADING":
      return { ...state, loading: action.payload };
    case "SET_ERROR":
      return { ...state, error: action.payload };
    default:
      return state;
  }
}

interface GoogleContextValue {
  state: GoogleState;
  setConnected: (connected: boolean) => void;
  setUser: (user: GoogleUser | null) => void;
  setLoading: (loading: boolean) => void;
  setError: (error: string | null) => void;
}

const GoogleContext = createContext<GoogleContextValue | null>(null);

function GoogleProvider({ children }: { children: ReactNode }) {
  const [state, dispatch] = useReducer(googleReducer, initialGoogleState);

  useEffect(() => {
    let unlisten: UnlistenFn | undefined;

    async function setup() {
      unlisten = await listen<GoogleStatusEvent>("google-status", (event) => {
        dispatch({ type: "SET_CONNECTED", payload: event.payload.connected });
        dispatch({ type: "SET_USER", payload: event.payload.user });
      });
    }

    setup();

    return () => {
      if (unlisten) {
        unlisten();
      }
    };
  }, []);

  const value = useMemo<GoogleContextValue>(
    () => ({
      state,
      setConnected: (connected: boolean) =>
        dispatch({ type: "SET_CONNECTED", payload: connected }),
      setUser: (user: GoogleUser | null) =>
        dispatch({ type: "SET_USER", payload: user }),
      setLoading: (loading: boolean) =>
        dispatch({ type: "SET_LOADING", payload: loading }),
      setError: (error: string | null) =>
        dispatch({ type: "SET_ERROR", payload: error }),
    }),
    [state],
  );

  return (
    <GoogleContext.Provider value={value}>
      {children}
    </GoogleContext.Provider>
  );
}

function useGoogle(): GoogleContextValue {
  const context = useContext(GoogleContext);
  if (!context) {
    throw new Error("useGoogle must be used within a GoogleProvider");
  }
  return context;
}

export { GoogleProvider, useGoogle };
export type { GoogleUser, GoogleState };
