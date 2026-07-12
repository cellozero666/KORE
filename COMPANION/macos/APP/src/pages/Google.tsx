import { useGoogleService } from "../hooks/useGoogle";
import "../assets/css/Google.css";

function Google() {
  const { state, connect, disconnect, checkMail, diagResult, diagLoading } =
    useGoogleService();
  const { connected, user, loading, error } = state;

  return (
    <div className="page google-page">
      <h2>Google</h2>

      {error && <div className="error">{error}</div>}

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

      {/* DIAGNÓSTICO TEMPORÁRIO — será removido antes da aprovação */}
      {connected && (
        <div className="google-diagnostic">
          <button
            className="diag-btn"
            onClick={checkMail}
            disabled={diagLoading}
          >
            {diagLoading ? "Verificando..." : "Checar Mail"}
          </button>

          {diagResult && (
            <div className="diag-result">
              <div className="diag-section">
                <strong>1. Timestamp usado:</strong> {diagResult.timestamp}
              </div>
              <div className="diag-section">
                <strong>2. Endpoint:</strong> {diagResult.endpoint}
              </div>
              <div className="diag-section">
                <strong>2. Query:</strong> {diagResult.query}
              </div>
              <div className="diag-section">
                <strong>3. Mensagens retornadas:</strong>{" "}
                {diagResult.messages_found}
              </div>
              {diagResult.message_ids.length > 0 && (
                <div className="diag-section">
                  <strong>4. IDs:</strong> {diagResult.message_ids.join(", ")}
                </div>
              )}
              {diagResult.messages.map((m, i) => (
                <div key={i} className="diag-message">
                  <div className="diag-section">
                    <strong>5. From:</strong> {m.from}
                  </div>
                  <div className="diag-section">
                    <strong>5. Subject:</strong> {m.subject}
                  </div>
                </div>
              ))}
              {diagResult.payloads.map((p, i) => (
                <div key={i} className="diag-section">
                  <strong>6. Payload:</strong> <code>{p}</code>
                </div>
              ))}
              <div className="diag-section">
                <strong>7. send_fire_forget() called:</strong>{" "}
                {diagResult.send_fire_forget_called ? "Sim" : "Não"}
              </div>
              <div className="diag-section">
                <strong>8. peripheral.write() result:</strong>{" "}
                {diagResult.peripheral_write_result}
              </div>
              {diagResult.error && (
                <div className="diag-section diag-error">
                  <strong>Erro:</strong> {diagResult.error}
                </div>
              )}
            </div>
          )}
        </div>
      )}
    </div>
  );
}

export default Google;
