import { useWeatherService } from "../hooks/useWeather";
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
      <h2>Clima</h2>

      {error && <div className="error">{error}</div>}

      {loading && !temperature && (
        <div className="weather-loading">Carregando...</div>
      )}

      {temperature != null && (
        <>
          <div className="weather-city">
            {city ?? "Localização desconhecida"}
          </div>

          <div className="weather-temp-display">
            <span className="weather-temp-value">{tempDisplay}</span>
            <span className="weather-condition">{condition}</span>
          </div>

          <div className="weather-details">
            <div className="weather-detail-item">
              <span className="weather-detail-label">Máxima</span>
              <span className="weather-detail-value">{maxDisplay}</span>
            </div>
            <div className="weather-detail-item">
              <span className="weather-detail-label">Mínima</span>
              <span className="weather-detail-value">{minDisplay}</span>
            </div>
          </div>

          <div className="weather-update">
            Última atualização: {lastUpdate ?? "--"}
          </div>
        </>
      )}
    </div>
  );
}

export default Weather;
