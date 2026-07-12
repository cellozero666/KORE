import { useSpotifyService } from "../hooks/useSpotify";
import "../assets/css/Spotify.css";

function formatTime(ms: number): string {
  const totalSec = Math.floor(ms / 1000);
  const min = Math.floor(totalSec / 60);
  const sec = totalSec % 60;
  return `${min}:${sec.toString().padStart(2, "0")}`;
}

function Spotify() {
  const { state, connect, disconnect, play, pause, next, previous } =
    useSpotifyService();
  const { connected, user, playback, loading, error } = state;

  return (
    <div className="page spotify-page">
      <h2>Spotify</h2>

      {/* Error */}
      {error && <div className="error">{error}</div>}

      {/* Account */}
      <div className="spotify-account">
        <div className={`spotify-status ${connected ? "connected" : "disconnected"}`}>
          {connected ? "Conectado" : "Desconectado"}
        </div>
        {user && (
          <div className="spotify-user">
            {user.image_url && (
              <img
                src={user.image_url}
                alt={user.display_name}
                className="spotify-avatar"
              />
            )}
            <span className="spotify-name">{user.display_name}</span>
          </div>
        )}
        <div className="spotify-actions">
          {connected ? (
            <button onClick={disconnect} disabled={loading}>
              Desconectar
            </button>
          ) : (
            <button onClick={connect} disabled={loading}>
              {loading ? "Conectando..." : "Conectar ao Spotify"}
            </button>
          )}
        </div>
      </div>

      {/* Playback */}
      {playback && (
        <div className="spotify-playback">
          <div className="spotify-track-info">
            {playback.album_art && (
              <img
                src={playback.album_art}
                alt={playback.album}
                className="spotify-album-art"
              />
            )}
            <div className="spotify-track-details">
              <div className="spotify-track-name">{playback.track}</div>
              <div className="spotify-artist-name">{playback.artist}</div>
              <div className="spotify-album-name">{playback.album}</div>
            </div>
          </div>

          {/* Progress */}
          <div className="spotify-progress">
            <div className="spotify-progress-bar">
              <div
                className="spotify-progress-fill"
                style={{
                  width: `${(playback.progress_ms / playback.duration_ms) * 100}%`,
                }}
              />
            </div>
            <div className="spotify-progress-times">
              <span>{formatTime(playback.progress_ms)}</span>
              <span>{formatTime(playback.duration_ms)}</span>
            </div>
          </div>

          {/* Controls */}
          <div className="spotify-controls">
            <button
              className="spotify-control-btn"
              onClick={previous}
              title="Anterior"
            >
              ⏮
            </button>
            <button
              className="spotify-control-btn spotify-play-btn"
              onClick={playback.is_playing ? pause : play}
              title={playback.is_playing ? "Pausar" : "Tocar"}
            >
              {playback.is_playing ? "⏸" : "▶"}
            </button>
            <button
              className="spotify-control-btn"
              onClick={next}
              title="Próxima"
            >
              ⏭
            </button>
          </div>
        </div>
      )}

      {/* No playback */}
      {connected && !playback && (
        <div className="spotify-empty">
          <p>Nenhuma reprodução ativa</p>
        </div>
      )}
    </div>
  );
}

export default Spotify;
