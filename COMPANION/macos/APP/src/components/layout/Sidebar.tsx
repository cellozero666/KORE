import { useNavigate, useLocation } from "react-router-dom";
import "../../assets/css/Sidebar.css";

const items = [
  { label: "Dashboard", path: "/" },
  { label: "Spotify", path: "/spotify" },
  { label: "Google", path: "/google" },
  { label: "Weather", path: "/weather" },
  { label: "Settings", path: "/settings" },
];

function Sidebar() {
  const navigate = useNavigate();
  const location = useLocation();

  return (
    <nav className="sidebar">
      <div className="sidebar-header">K.O.R.E.</div>
      <ul className="sidebar-nav">
        {items.map((item) => (
          <li key={item.path}>
            <button
              className={`sidebar-item ${location.pathname === item.path ? "active" : ""}`}
              onClick={() => navigate(item.path)}
            >
              {item.label}
            </button>
          </li>
        ))}
      </ul>
    </nav>
  );
}

export default Sidebar;
