import { useState, useEffect } from "react";
import { HashRouter, Routes, Route } from "react-router-dom";
import LoadingScreen from "../common/LoadingScreen";
import Sidebar from "./Sidebar";
import Dashboard from "../../pages/Dashboard";
import Spotify from "../../pages/Spotify";
import Google from "../../pages/Google";
import Weather from "../../pages/Weather";
import Settings from "../../pages/Settings";
import "../../assets/css/App.css";

function App() {
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    const timer = setTimeout(() => {
      setLoading(false);
    }, 5000);
    return () => clearTimeout(timer);
  }, []);

  if (loading) {
    return <LoadingScreen />;
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
