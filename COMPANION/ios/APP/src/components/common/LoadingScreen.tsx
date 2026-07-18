import { KoreIcon } from "./KoreIcon";
import "../../assets/css/LoadingScreen.css";

interface LoadingScreenProps {
  error?: string | null;
  onRetry?: () => void;
  diagnosticStep?: string | null;
  diagnosticElapsed?: number;
}

const DIAG_TIMEOUT = 15;

function LoadingScreen({
  error,
  onRetry,
  diagnosticStep,
  diagnosticElapsed = 0,
}: LoadingScreenProps) {
  const showDiagnostic =
    !error && diagnosticElapsed >= DIAG_TIMEOUT && diagnosticStep;

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
        <>
          <KoreIcon className="loading-icon" />
          {showDiagnostic && (
            <div className="loading-diagnostic">
              <p className="loading-diagnostic-state">Current State:</p>
              <p className="loading-diagnostic-step">{diagnosticStep}</p>
              <p className="loading-diagnostic-time">
                {diagnosticElapsed}s elapsed
              </p>
            </div>
          )}
        </>
      )}
    </div>
  );
}

export default LoadingScreen;
