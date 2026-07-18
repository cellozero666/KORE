import { useNavigate, useLocation } from "react-router-dom";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { KoreIcon } from "../common/KoreIcon";
import items from "./sidebarItems";
import "../../assets/css/Sidebar.css";

function Sidebar() {
  const navigate = useNavigate();
  const location = useLocation();

  return (
    <nav className="sidebar">
      <div className="sidebar-header">
        <KoreIcon className="sidebar-logo" />
        <span className="sidebar-title">K.O.R.E.</span>
      </div>
      <ul className="sidebar-nav">
        {items.map((item) => (
          <li key={item.path}>
            <button
              className={`sidebar-item ${location.pathname === item.path ? "active" : ""}`}
              onClick={() => navigate(item.path)}
            >
              <FontAwesomeIcon icon={item.icon} className="sidebar-icon" />
              <span className="sidebar-label">{item.label}</span>
            </button>
          </li>
        ))}
      </ul>
    </nav>
  );
}

export default Sidebar;
