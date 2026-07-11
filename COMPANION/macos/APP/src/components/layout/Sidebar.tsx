import "../../assets/css/Sidebar.css";

type Section = "Dashboard" | "Spotify" | "Google" | "Weather" | "Settings";

interface SidebarProps {
  activeItem: Section;
  onItemClick: (item: Section) => void;
}

const items: Section[] = [
  "Dashboard",
  "Spotify",
  "Google",
  "Weather",
  "Settings",
];

function Sidebar({ activeItem, onItemClick }: SidebarProps) {
  return (
    <nav className="sidebar">
      <div className="sidebar-header">K.O.R.E.</div>
      <ul className="sidebar-nav">
        {items.map((item) => (
          <li key={item}>
            <button
              className={`sidebar-item ${activeItem === item ? "active" : ""}`}
              onClick={() => onItemClick(item)}
            >
              {item}
            </button>
          </li>
        ))}
      </ul>
    </nav>
  );
}

export default Sidebar;
