import { useGoogleService } from "../hooks/useGoogle";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faGoogle } from "@fortawesome/free-brands-svg-icons";
import { faPlug, faPlugCircleXmark, faEnvelope } from "@fortawesome/free-solid-svg-icons";
import "../assets/css/Google.css";

function Google() {
  const { state, connect, disconnect } = useGoogleService();
  const { connected, user, loading } = state;

  return (
    <div className="page google-page">
      <header className="google-header">
        <h2>
          <FontAwesomeIcon icon={faGoogle} /> Google
        </h2>
        <div className={`google-status ${connected ? "connected" : "disconnected"}`}>
          {connected ? "Connected" : "Disconnected"}
        </div>
      </header>

      <div className="google-container">
        <div className="google-account">
          {user && (
            <div className="google-user">
              {user.image_url && (
                <img src={user.image_url} alt={user.display_name} className="google-avatar" />
              )}
              <div className="google-user-info">
                <span className="google-name">{user.display_name}</span>
                <span className="google-email">{user.email}</span>
              </div>
            </div>
          )}
          
          <div className="google-actions">
            <button className="google-btn" onClick={connected ? disconnect : connect} disabled={loading}>
              <FontAwesomeIcon icon={connected ? faPlugCircleXmark : faPlug} />
              {loading ? "..." : connected ? "Disconnect" : "Connect"}
            </button>
            <button className="google-btn" onClick={() => {}}>
                <FontAwesomeIcon icon={faEnvelope} /> Check Mail
            </button>
          </div>
        </div>
      </div>
    </div>
  );
}

export default Google;
