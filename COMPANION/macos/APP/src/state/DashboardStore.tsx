import { createContext, useContext, useReducer, type ReactNode } from "react";

interface DashboardState {}

type DashboardAction = never;

const initialDashboardState: DashboardState = {};

function dashboardReducer(
  state: DashboardState,
  _action: DashboardAction
): DashboardState {
  return state;
}

interface DashboardContextValue {
  state: DashboardState;
}

const DashboardContext = createContext<DashboardContextValue | null>(null);

function DashboardProvider({ children }: { children: ReactNode }) {
  const [state] = useReducer(dashboardReducer, initialDashboardState);

  return (
    <DashboardContext.Provider value={{ state }}>
      {children}
    </DashboardContext.Provider>
  );
}

function useDashboard(): DashboardContextValue {
  const context = useContext(DashboardContext);
  if (!context) {
    throw new Error("useDashboard must be used within a DashboardProvider");
  }
  return context;
}

export { DashboardProvider, useDashboard };
