import { faGauge, faCloud, faGear } from '@fortawesome/free-solid-svg-icons';
import { faSpotify, faGoogle } from '@fortawesome/free-brands-svg-icons';

const items = [
  { label: "Dashboard", path: "/", icon: faGauge },
  { label: "Spotify", path: "/spotify", icon: faSpotify },
  { label: "Google", path: "/google", icon: faGoogle },
  { label: "Weather", path: "/weather", icon: faCloud },
  { label: "Settings", path: "/settings", icon: faGear },
];
export default items;
