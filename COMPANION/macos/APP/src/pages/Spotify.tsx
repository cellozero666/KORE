import { useSpotifyService } from "../hooks/useSpotify";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faSpotify } from "@fortawesome/free-brands-svg-icons";
import { faBackward, faForward, faPlay, faPause, faPlug, faPlugCircleXmark } from "@fortawesome/free-solid-svg-icons";
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
      <header className="spotify-header">
        <h2>
          <FontAwesomeIcon icon={faSpotify} /> Spotify
        </h2>
        <div className={`spotify-status ${connected ? "connected" : "disconnected"}`}>
          {connected ? "Connected" : "Disconnected"}
        </div>
      </header>

      {/* Error */}
      {error && <div className="error">{error}</div>}

      <div className="spotify-container">
        {/* Account */}
        <div className="spotify-account">
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
          <button className="spotify-connect-btn" onClick={connected ? disconnect : connect} disabled={loading}>
            <FontAwesomeIcon icon={connected ? faPlugCircleXmark : faPlug} /> 
            {loading ? "..." : connected ? "Disconnect" : "Connect"}
          </button>
        </div>

        {/* Playback */}
        {playback && (
          <div className="spotify-playback">
            {playback.album_art && (
              <img
                src={playback.album_art}
                alt={playback.album}
                className="spotify-album-art"
              />
            )}
            
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

            <div className="spotify-track-details">
              <div className="spotify-track-name">{playback.track}</div>
              <div className="spotify-artist-name">{playback.artist}</div>
              <div className="spotify-album-name">{playback.album}</div>
            </div>

            <div className="spotify-controls">
              <button className="spotify-control-btn" onClick={previous}><FontAwesomeIcon icon={faBackward} /></button>
              <button className="spotify-control-btn spotify-play-btn" onClick={playback.is_playing ? pause : play}>
                <FontAwesomeIcon icon={playback.is_playing ? faPause : faPlay} />
              </button>
              <button className="spotify-control-btn" onClick={next}><FontAwesomeIcon icon={faForward} /></button>
            </div>
          </div>
        )}
      </div>

      {/* No playback */}
      {connected && !playback && <div className="spotify-empty"><p>No active playback</p></div>}
    </div>
  );
}

export default Spotify;
