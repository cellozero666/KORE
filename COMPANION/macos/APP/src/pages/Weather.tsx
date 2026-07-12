import { useWeatherService } from "../hooks/useWeather";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faCloudSun, faTemperatureHigh, faTemperatureLow, faSync } from "@fortawesome/free-solid-svg-icons";
import "../assets/css/Weather.css";

function Weather() {
  const {
    city, temperature, maxTemperature, minTemperature,
    condition, lastUpdate, loading, error,
  } = useWeatherService();

  const tempDisplay = temperature != null ? `${Math.round(temperature)}°` : "--";
  const maxDisplay = maxTemperature != null ? `${Math.round(maxTemperature)}°` : "--";
  const minDisplay = minTemperature != null ? `${Math.round(minTemperature)}°` : "--";

  return (
    <div className="page weather-page">
      <header className="weather-header">
        <h2>
          <FontAwesomeIcon icon={faCloudSun} /> Weather
        </h2>
      </header>

      {error && <div className="error">{error}</div>}

      {loading && !temperature && (
        <div className="weather-loading">Loading...</div>
      )}

      {temperature != null && (
        <div className="weather-container">
          <div className="weather-city">
            {city ?? "Unknown Location"}
          </div>

          <div className="weather-temp-display">
            <span className="weather-temp-value">{tempDisplay}</span>
            <span className="weather-condition">{condition}</span>
          </div>

          <div className="weather-details">
            <div className="weather-detail-item">
              <span className="weather-detail-label">
                <FontAwesomeIcon icon={faTemperatureHigh} /> High
              </span>
              <span className="weather-detail-value">{maxDisplay}</span>
            </div>
            <div className="weather-detail-item">
              <span className="weather-detail-label">
                <FontAwesomeIcon icon={faTemperatureLow} /> Low
              </span>
              <span className="weather-detail-value">{minDisplay}</span>
            </div>
          </div>

          <div className="weather-update">
            <FontAwesomeIcon icon={faSync} /> Last Update: {lastUpdate ?? "--"}
          </div>
        </div>
      )}
    </div>
  );
}

export default Weather;
