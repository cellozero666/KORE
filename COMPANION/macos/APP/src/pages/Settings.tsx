import { useState, useEffect, useRef, useCallback } from "react";
import { useSettingsService, type CityOption } from "../hooks/useSettings";
import { COUNTRIES } from "../utils/countries";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faGear, faLocationDot, faWifi, faLock, faSave, faPlug } from "@fortawesome/free-solid-svg-icons";
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

  useEffect(() => {
    if (location) {
      setAutodetect(location.autodetect);
      setCountry(location.country);
      setCity(location.city);
    }
  }, [location]);

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
  };

  const handleWifiConnect = async () => {
    if (!wifiSsid || !wifiPassword) return;
    await connectWifi(wifiSsid, wifiPassword);
  };

  return (
    <div className="page settings-page">
      <header className="settings-header">
        <h2>
          <FontAwesomeIcon icon={faGear} /> Settings
        </h2>
      </header>

      {error && <div className="error">{error}</div>}

      <div className="settings-container">
        {/* Location Section */}
        <section className="settings-card">
          <h3><FontAwesomeIcon icon={faLocationDot} /> Location</h3>

          <div className="settings-field checkbox">
            <input
              type="checkbox"
              id="autodetect"
              checked={autodetect}
              onChange={(e) => setAutodetect(e.target.checked)}
            />
            <label htmlFor="autodetect">Auto Detect</label>
          </div>

          <div className="settings-field">
            <label htmlFor="country">Country</label>
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
              <option value="">Select country</option>
              {COUNTRIES.map((c) => (
                <option key={c.value} value={c.value}>{c.label}</option>
              ))}
            </select>
          </div>

          <div className="settings-field">
            <label htmlFor="city">City</label>
            <div className="settings-city-search">
              <input
                type="text"
                id="city"
                placeholder="City name..."
                value={autodetect ? "Automatic" : (cityQuery || city)}
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
                disabled={autodetect}
              />
              {searching && (
                <div className="settings-city-result">Searching...</div>
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
          </div>

          <button className="settings-btn" onClick={handleSave} disabled={loading}>
            <FontAwesomeIcon icon={faSave} /> {loading ? "Saving..." : "Save Location"}
          </button>
        </section>

        {/* WiFi Section */}
        <section className="settings-card">
          <h3><FontAwesomeIcon icon={faWifi} /> Wi-Fi</h3>

          <div className="settings-field">
            <label htmlFor="wifi-ssid">SSID</label>
            <input
              type="text"
              id="wifi-ssid"
              value={wifiSsid}
              onChange={(e) => setWifiSsid(e.target.value)}
              placeholder="Network name"
            />
          </div>

          <div className="settings-field">
            <label htmlFor="wifi-password"><FontAwesomeIcon icon={faLock} /> Password</label>
            <input
              type="password"
              id="wifi-password"
              value={wifiPassword}
              onChange={(e) => setWifiPassword(e.target.value)}
              placeholder="Network password"
            />
          </div>

          <button className="settings-btn" onClick={handleWifiConnect} disabled={loading}>
            <FontAwesomeIcon icon={faPlug} /> {loading ? "Connecting..." : "Connect"}
          </button>
        </section>
      </div>
    </div>
  );
}

export default Settings;
