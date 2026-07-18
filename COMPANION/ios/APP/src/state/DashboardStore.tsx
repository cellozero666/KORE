import {
  createContext,
  useCallback,
  useContext,
  useMemo,
  useReducer,
  type ReactNode,
} from "react";

interface WifiStatus {
  connected: boolean;
  ipAddress: string | null;
}

interface DashboardState {
  firmwareVersion: string | null;
  firmwareVersionLoading: boolean;
  uptime: string | null;
  uptimeLoading: boolean;
  wifiStatus: WifiStatus | null;
  wifiStatusLoading: boolean;
}

type DashboardAction =
  | { type: "SET_FIRMWARE_VERSION"; payload: string }
  | { type: "SET_FIRMWARE_VERSION_LOADING"; payload: boolean }
  | { type: "SET_UPTIME"; payload: string }
  | { type: "SET_UPTIME_LOADING"; payload: boolean }
  | { type: "SET_WIFI_STATUS"; payload: WifiStatus }
  | { type: "SET_WIFI_STATUS_LOADING"; payload: boolean };

const initialDashboardState: DashboardState = {
  firmwareVersion: null,
  firmwareVersionLoading: true,
  uptime: null,
  uptimeLoading: true,
  wifiStatus: null,
  wifiStatusLoading: true,
};

function dashboardReducer(
  state: DashboardState,
  action: DashboardAction,
): DashboardState {
  switch (action.type) {
    case "SET_FIRMWARE_VERSION":
      return { ...state, firmwareVersion: action.payload, firmwareVersionLoading: false };
    case "SET_FIRMWARE_VERSION_LOADING":
      return { ...state, firmwareVersionLoading: action.payload };
    case "SET_UPTIME":
      return { ...state, uptime: action.payload, uptimeLoading: false };
    case "SET_UPTIME_LOADING":
      return { ...state, uptimeLoading: action.payload };
    case "SET_WIFI_STATUS":
      return { ...state, wifiStatus: action.payload, wifiStatusLoading: false };
    case "SET_WIFI_STATUS_LOADING":
      return { ...state, wifiStatusLoading: action.payload };
    default:
      return state;
  }
}

interface DashboardContextValue {
  state: DashboardState;
  setFirmwareVersion: (version: string) => void;
  setFirmwareVersionLoading: (loading: boolean) => void;
  setUptime: (uptime: string) => void;
  setUptimeLoading: (loading: boolean) => void;
  setWifiStatus: (status: WifiStatus) => void;
  setWifiStatusLoading: (loading: boolean) => void;
}

const DashboardContext = createContext<DashboardContextValue | null>(null);

function DashboardProvider({ children }: { children: ReactNode }) {
  const [state, dispatch] = useReducer(dashboardReducer, initialDashboardState);

  const setFirmwareVersion = useCallback(
    (version: string) => dispatch({ type: "SET_FIRMWARE_VERSION", payload: version }),
    [],
  );
  const setFirmwareVersionLoading = useCallback(
    (loading: boolean) => dispatch({ type: "SET_FIRMWARE_VERSION_LOADING", payload: loading }),
    [],
  );
  const setUptime = useCallback(
    (uptime: string) => dispatch({ type: "SET_UPTIME", payload: uptime }),
    [],
  );
  const setUptimeLoading = useCallback(
    (loading: boolean) => dispatch({ type: "SET_UPTIME_LOADING", payload: loading }),
    [],
  );
  const setWifiStatus = useCallback(
    (status: WifiStatus) => dispatch({ type: "SET_WIFI_STATUS", payload: status }),
    [],
  );
  const setWifiStatusLoading = useCallback(
    (loading: boolean) => dispatch({ type: "SET_WIFI_STATUS_LOADING", payload: loading }),
    [],
  );

  const value = useMemo<DashboardContextValue>(
    () => ({
      state,
      setFirmwareVersion,
      setFirmwareVersionLoading,
      setUptime,
      setUptimeLoading,
      setWifiStatus,
      setWifiStatusLoading,
    }),
    [state],
  );

  return (
    <DashboardContext.Provider value={value}>
      {children}
    </DashboardContext.Provider>
  );
}

function useDashboardStore(): DashboardContextValue {
  const context = useContext(DashboardContext);
  if (!context) {
    throw new Error("useDashboardStore must be used within a DashboardProvider");
  }
  return context;
}

export { DashboardProvider, useDashboardStore };
