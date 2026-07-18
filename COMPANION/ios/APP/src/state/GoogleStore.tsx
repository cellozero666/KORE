import {
  createContext,
  useContext,
  useMemo,
  useReducer,
  type ReactNode,
} from "react";

interface GoogleUser {
  id: string;
  display_name: string;
  email: string;
  image_url: string | null;
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
  setLoading: (loading: boolean) => void;
  setError: (error: string | null) => void;
}

const GoogleContext = createContext<GoogleContextValue | null>(null);

function GoogleProvider({ children }: { children: ReactNode }) {
  const [state, dispatch] = useReducer(googleReducer, initialGoogleState);

  const value = useMemo<GoogleContextValue>(
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
