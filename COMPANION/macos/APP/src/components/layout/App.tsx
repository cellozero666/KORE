import { useState, useEffect } from "react";
import LoadingScreen from "../common/LoadingScreen";
import Sidebar from "./Sidebar";
import "../../assets/css/App.css";

type Section = "Dashboard" | "Spotify" | "Google" | "Weather" | "Settings";

function App() {
  const [loading, setLoading] = useState(true);
  const [activeSection, setActiveSection] = useState<Section>("Dashboard");

  useEffect(() => {
    const timer = setTimeout(() => setLoading(false), 5000);
    return () => clearTimeout(timer);
  }, []);

  if (loading) {
    return <LoadingScreen />;
  }

  return (
    <div className="layout">
      <Sidebar activeItem={activeSection} onItemClick={setActiveSection} />
      <main className="content">
        <h2>{activeSection}</h2>
        <p className="placeholder">Módulo em desenvolvimento</p>
      </main>
    </div>
  );
}

export default App;
