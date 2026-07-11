import { HashRouter, Routes, Route } from "react-router-dom";
import { StoreProvider, useApp } from "../../state";
import { useConnection } from "../../hooks/useConnection";
import LoadingScreen from "../common/LoadingScreen";
import Sidebar from "./Sidebar";
import Dashboard from "../../pages/Dashboard";
import Spotify from "../../pages/Spotify";
import Google from "../../pages/Google";
import Weather from "../../pages/Weather";
import Settings from "../../pages/Settings";
import "../../assets/css/App.css";

function App() {
  return (
    <StoreProvider>
      <AppContent />
    </StoreProvider>
  );
}

function AppContent() {
  const { state } = useApp();
  const { startConnection } = useConnection();

  if (state.loading && !state.error) {
    return <LoadingScreen />;
  }

  if (state.error && !state.loading) {
    return <LoadingScreen error={state.error} onRetry={startConnection} />;
  }

  return (
    <HashRouter>
      <div className="layout">
        <Sidebar />
        <main className="content">
          <Routes>
            <Route path="/" element={<Dashboard />} />
            <Route path="/spotify" element={<Spotify />} />
            <Route path="/google" element={<Google />} />
            <Route path="/weather" element={<Weather />} />
            <Route path="/settings" element={<Settings />} />
          </Routes>
        </main>
      </div>
    </HashRouter>
  );
}

export default App;
