import { KoreIcon } from "./KoreIcon";
import "../../assets/css/LoadingScreen.css";

interface LoadingScreenProps {
  error?: string | null;
  onRetry?: () => void;
}

function LoadingScreen({ error, onRetry }: LoadingScreenProps) {
  return (
    <div className="loading-screen">
      <h1 className="loading-title">K.O.R.E.</h1>
      <p className="loading-subtitle">Companion</p>

      {error ? (
        <>
          <p className="loading-error">{error}</p>
          {onRetry && (
            <button className="loading-retry" onClick={onRetry}>
              Try Again
            </button>
          )}
        </>
      ) : (
        <KoreIcon className="loading-icon" />
      )}
    </div>
  );
}

export default LoadingScreen;
