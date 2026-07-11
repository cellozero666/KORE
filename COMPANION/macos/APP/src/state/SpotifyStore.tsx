import { createContext, useContext, useReducer, type ReactNode } from "react";

interface SpotifyState {}

type SpotifyAction = never;

const initialSpotifyState: SpotifyState = {};

function spotifyReducer(
  state: SpotifyState,
  _action: SpotifyAction
): SpotifyState {
  return state;
}

interface SpotifyContextValue {
  state: SpotifyState;
}

const SpotifyContext = createContext<SpotifyContextValue | null>(null);

function SpotifyProvider({ children }: { children: ReactNode }) {
  const [state] = useReducer(spotifyReducer, initialSpotifyState);

  return (
    <SpotifyContext.Provider value={{ state }}>
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
