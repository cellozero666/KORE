import { createContext, useContext, useReducer, type ReactNode } from "react";

interface GoogleState {}

type GoogleAction = never;

const initialGoogleState: GoogleState = {};

function googleReducer(
  state: GoogleState,
  _action: GoogleAction
): GoogleState {
  return state;
}

interface GoogleContextValue {
  state: GoogleState;
}

const GoogleContext = createContext<GoogleContextValue | null>(null);

function GoogleProvider({ children }: { children: ReactNode }) {
  const [state] = useReducer(googleReducer, initialGoogleState);

  return (
    <GoogleContext.Provider value={{ state }}>
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
