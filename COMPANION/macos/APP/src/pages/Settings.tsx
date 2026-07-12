import { useState, useEffect, useRef, useCallback } from "react";
import { useSettingsService, type CityOption } from "../hooks/useSettings";
import { COUNTRIES } from "../utils/countries";
import "../assets/css/Settings.css";

function Settings() {
  const {
    location, loading, error,
    wifiSsid, wifiPassword, setWifiSsid, setWifiPassword,
    saveLocation, searchCities, connectWifi,
  } = useSettingsService();

  const [autodetect, setAutodetect] = useState(true);
  const [country, setCountry] = useState("");
  const [city, setCity] = useState("");
  const [cityQuery, setCityQuery] = useState("");
  const [cityResults, setCityResults] = useState<CityOption[]>([]);
  const [showResults, setShowResults] = useState(false);
  const [searching, setSearching] = useState(false);

  const debounceRef = useRef<ReturnType<typeof setTimeout> | null>(null);

  // Sync state when location loads
  useEffect(() => {
    if (location) {
      setAutodetect(location.autodetect);
      setCountry(location.country);
      setCity(location.city);
    }
  }, [location]);

  // City search with debounce
  const handleCitySearch = useCallback(
    (query: string) => {
      setCityQuery(query);
      if (debounceRef.current) clearTimeout(debounceRef.current);

      if (query.length < 2) {
        setCityResults([]);
        setShowResults(false);
        return;
      }

      debounceRef.current = setTimeout(async () => {
        setSearching(true);
        const results = await searchCities(query, country);
        setCityResults(results);
        setShowResults(results.length > 0);
        setSearching(false);
      }, 400);
    },
    [country, searchCities],
  );

  const selectCity = (option: CityOption) => {
    setCity(option.name);
    setCityQuery(option.name);
    setShowResults(false);
    setCountry(option.country_code);
  };

  const handleSave = async () => {
    const config = {
      autodetect,
      country: autodetect ? "" : country,
      city: autodetect ? "" : cityQuery || city,
      latitude: 0.0,
      longitude: 0.0,
    };
    await saveLocation(config);
    if (autodetect) {
      setCity("");
      setCityQuery("");
      setCountry("");
    }
  };

  const handleWifiConnect = async () => {
    if (!wifiSsid || !wifiPassword) return;
    await connectWifi(wifiSsid, wifiPassword);
  };

  return (
    <div className="page settings-page">
      <h2>Configurações</h2>

      {error && <div className="error">{error}</div>}

      {loading && !location && (
        <div className="weather-loading">Carregando...</div>
      )}

      {/* Location */}
      <div className="settings-section">
        <h3>Localização</h3>

        <div className="settings-checkbox">
          <input
            type="checkbox"
            id="autodetect"
            checked={autodetect}
            onChange={(e) => setAutodetect(e.target.checked)}
          />
          <label htmlFor="autodetect">Detecção automática</label>
        </div>

        <div className="settings-field">
          <label htmlFor="country">País</label>
          <select
            id="country"
            value={country}
            onChange={(e) => {
              setCountry(e.target.value);
              setCity("");
              setCityQuery("");
            }}
            disabled={autodetect}
          >
            <option value="">Selecione um país</option>
            {COUNTRIES.map((c) => (
              <option key={c.value} value={c.value}>
                {c.label}
              </option>
            ))}
          </select>
        </div>

        <div className="settings-field">
          <label htmlFor="city">Cidade</label>
          {autodetect ? (
            <input
              type="text"
              id="city"
              value="Automático"
              disabled
            />
          ) : (
            <div className="settings-city-search">
              <input
                type="text"
                id="city"
                placeholder="Digite o nome da cidade..."
                value={cityQuery || city}
                onChange={(e) => {
                  setCity("");
                  handleCitySearch(e.target.value);
                }}
                onFocus={() => {
                  if (cityResults.length > 0) setShowResults(true);
                }}
                onBlur={() => {
                  setTimeout(() => setShowResults(false), 200);
                }}
              />
              {searching && (
                <div className="settings-city-result" style={{ position: "absolute", top: "100%", left: 0, right: 0, background: "#1a1a1a", border: "1px solid #333", borderTop: "none", borderRadius: "0 0 6px 6px", padding: "0.6rem 0.75rem", fontSize: "0.9rem", color: "#888" }}>
                  Buscando...
                </div>
              )}
              {showResults && !searching && (
                <div className="settings-city-results">
                  {cityResults.map((r, i) => (
                    <div
                      key={`${r.latitude}-${r.longitude}-${i}`}
                      className="settings-city-result"
                      onMouseDown={() => selectCity(r)}
                    >
                      {r.name}
                      <span className="city-country">{r.country}</span>
                    </div>
                  ))}
                </div>
              )}
            </div>
          )}
        </div>

        <button
          className="settings-btn settings-btn-primary"
          onClick={handleSave}
          disabled={loading}
        >
          {loading ? "Salvando..." : "Salvar Localização"}
        </button>
      </div>

      {/* WiFi */}
      <div className="settings-section">
        <h3>Wi-Fi</h3>

        <div className="settings-field">
          <label htmlFor="wifi-ssid">SSID</label>
          <input
            type="text"
            id="wifi-ssid"
            value={wifiSsid}
            onChange={(e) => setWifiSsid(e.target.value)}
            placeholder="Nome da rede"
          />
        </div>

        <div className="settings-field">
          <label htmlFor="wifi-password">Senha</label>
          <input
            type="password"
            id="wifi-password"
            value={wifiPassword}
            onChange={(e) => setWifiPassword(e.target.value)}
            placeholder="Senha da rede"
          />
        </div>

        <button
          className="settings-btn settings-btn-wifi"
          onClick={handleWifiConnect}
          disabled={loading || !wifiSsid || !wifiPassword}
        >
          {loading ? "Conectando..." : "Conectar Wi-Fi"}
        </button>
      </div>
    </div>
  );
}

export default Settings;
