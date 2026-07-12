import { useGoogleService } from "../hooks/useGoogle";
import "../assets/css/Google.css";

function Google() {
  const { state, connect, disconnect } =
    useGoogleService();
  const { connected, user, loading } = state;

  return (
    <div className="page google-page">
      <h2>Google</h2>

      <div className="google-account">
        <div className={`google-status ${connected ? "connected" : "disconnected"}`}>
          {connected ? "Conectado" : "Desconectado"}
        </div>
        {user && (
          <div className="google-user">
            {user.image_url && (
              <img
                src={user.image_url}
                alt={user.display_name}
                className="google-avatar"
              />
            )}
            <div className="google-user-info">
              <span className="google-name">{user.display_name}</span>
              <span className="google-email">{user.email}</span>
            </div>
          </div>
        )}
        <div className="google-actions">
          {connected ? (
            <button onClick={disconnect} disabled={loading}>
              Desconectar
            </button>
          ) : (
            <button onClick={connect} disabled={loading}>
              {loading ? "Conectando..." : "Conectar ao Google"}
            </button>
          )}
        </div>
      </div>
    </div>
  );
}

export default Google;
