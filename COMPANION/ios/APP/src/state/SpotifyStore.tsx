import {
  createContext,
  useContext,
  useMemo,
  useReducer,
  type ReactNode,
} from "react";

interface SpotifyUser {
  id: string;
  display_name: string;
  image_url: string | null;
}

interface SpotifyPlayback {
  track: string;
  artist: string;
  album: string;
  album_art: string | null;
  progress_ms: number;
  duration_ms: number;
  is_playing: boolean;
}

interface SpotifyState {
  connected: boolean;
  user: SpotifyUser | null;
  playback: SpotifyPlayback | null;
  loading: boolean;
  error: string | null;
}

type SpotifyAction =
  | { type: "SET_CONNECTED"; payload: boolean }
  | { type: "SET_USER"; payload: SpotifyUser | null }
  | { type: "SET_PLAYBACK"; payload: SpotifyPlayback | null }
  | { type: "SET_LOADING"; payload: boolean }
  | { type: "SET_ERROR"; payload: string | null };

const initialSpotifyState: SpotifyState = {
  connected: false,
  user: null,
  playback: null,
  loading: false,
  error: null,
};

function spotifyReducer(
  state: SpotifyState,
  action: SpotifyAction,
): SpotifyState {
  switch (action.type) {
    case "SET_CONNECTED":
      return { ...state, connected: action.payload };
    case "SET_USER":
      return { ...state, user: action.payload };
    case "SET_PLAYBACK":
      return { ...state, playback: action.payload };
    case "SET_LOADING":
      return { ...state, loading: action.payload };
    case "SET_ERROR":
      return { ...state, error: action.payload };
    default:
      return state;
  }
}

interface SpotifyContextValue {
  state: SpotifyState;
  setPlayback: (playback: SpotifyPlayback | null) => void;
  setLoading: (loading: boolean) => void;
  setError: (error: string | null) => void;
}

const SpotifyContext = createContext<SpotifyContextValue | null>(null);

function SpotifyProvider({ children }: { children: ReactNode }) {
  const [state, dispatch] = useReducer(spotifyReducer, initialSpotifyState);

  const value = useMemo<SpotifyContextValue>(
    () => ({
      state,
      setPlayback: (playback: SpotifyPlayback | null) =>
        dispatch({ type: "SET_PLAYBACK", payload: playback }),
      setLoading: (loading: boolean) =>
        dispatch({ type: "SET_LOADING", payload: loading }),
      setError: (error: string | null) =>
        dispatch({ type: "SET_ERROR", payload: error }),
    }),
    [state],
  );

  return (
    <SpotifyContext.Provider value={value}>
      {children}
    </SpotifyContext.Provider>
  );
}

function useSpotify(): SpotifyContextValue {
  const context = useContext(SpotifyContext);
  if (!context) {
    throw new Error("useSpotify must be used within a SpotifyProvider");
  }
  return context;
}

export { SpotifyProvider, useSpotify };
