import { createContext, useContext, useReducer, type ReactNode } from "react";

interface SettingsState {}

type SettingsAction = never;

const initialSettingsState: SettingsState = {};

function settingsReducer(
  state: SettingsState,
  _action: SettingsAction
): SettingsState {
  return state;
}

interface SettingsContextValue {
  state: SettingsState;
}

const SettingsContext = createContext<SettingsContextValue | null>(null);

function SettingsProvider({ children }: { children: ReactNode }) {
  const [state] = useReducer(settingsReducer, initialSettingsState);

  return (
    <SettingsContext.Provider value={{ state }}>
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
