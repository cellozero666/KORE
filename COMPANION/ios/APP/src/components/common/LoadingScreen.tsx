import { KoreIcon } from "./KoreIcon";
import "../../assets/css/LoadingScreen.css";

function LoadingScreen() {
  return (
    <div className="loading-screen">
      <h1 className="loading-title">K.O.R.E.</h1>
      <p className="loading-subtitle">Companion</p>
      <KoreIcon className="loading-icon" />
    </div>
  );
}

export default LoadingScreen;
