import type { ReactNode } from "react";
import { AppProvider } from "./AppStore";
import { DashboardProvider } from "./DashboardStore";
import { SpotifyProvider } from "./SpotifyStore";
import { GoogleProvider } from "./GoogleStore";
import { WeatherProvider } from "./WeatherStore";
import { SettingsProvider } from "./SettingsStore";

function StoreProvider({ children }: { children: ReactNode }) {
  return (
    <AppProvider>
      <DashboardProvider>
        <SpotifyProvider>
          <GoogleProvider>
            <WeatherProvider>
              <SettingsProvider>{children}</SettingsProvider>
            </WeatherProvider>
          </GoogleProvider>
        </SpotifyProvider>
      </DashboardProvider>
    </AppProvider>
  );
}

export default StoreProvider;
