#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>

extern String wifiSSID;
extern String wifiPassword;
extern bool wifiConnecting;
extern unsigned long wifiConnectStarted;

void saveWiFiCredentials(String ssid, String password);
void loadWiFiCredentials();
void connectWiFi(String ssid, String password);
void autoConnectWiFi();
void updateWiFiManager();
String getWiFiStatus();

#endif
