#include <Arduino.h>
#include <WiFi.h>
#include <Preferences.h>
#include "wifi_manager.h"

String wifiSSID = "";
String wifiPassword = "";
bool wifiConnecting = false;
unsigned long wifiConnectStarted = 0;

static Preferences wifiPrefs;

void saveWiFiCredentials(String ssid, String password)
{
    wifiPrefs.begin("wifi", false);
    wifiPrefs.putString("ssid", ssid);
    wifiPrefs.putString("password", password);
    wifiPrefs.end();
}

void loadWiFiCredentials()
{
    wifiPrefs.begin("wifi", true);
    wifiSSID = wifiPrefs.getString("ssid", "");
    wifiPassword = wifiPrefs.getString("password", "");
    wifiPrefs.end();
}

void connectWiFi(String ssid, String password)
{
    wifiSSID = ssid;
    wifiPassword = password;
    saveWiFiCredentials(ssid, password);
    Serial.print("Connecting to ");
    Serial.println(wifiSSID);
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
    wifiConnecting = true;
    wifiConnectStarted = millis();
}

void autoConnectWiFi()
{
    loadWiFiCredentials();
    if (wifiSSID.length() == 0)
    {
        Serial.println("No WiFi credentials saved");
        return;
    }
    Serial.print("Auto connecting to ");
    Serial.println(wifiSSID);
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
    wifiConnecting = true;
    wifiConnectStarted = millis();
}

void updateWiFiManager()
{
    if (!wifiConnecting)
        return;

    if (WiFi.status() == WL_CONNECTED)
    {
        wifiConnecting = false;
        Serial.println("WIFI_CONNECTED");
        return;
    }

    if (millis() - wifiConnectStarted > 15000UL)
    {
        wifiConnecting = false;
        Serial.println("WIFI_FAILED");
    }
}

String getWiFiStatus()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return "CONNECTED|" + WiFi.SSID() + "|" + WiFi.localIP().toString();
    }
    return "DISCONNECTED";
}
