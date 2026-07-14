#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <Arduino.h>

class Adafruit_ST7789;

extern unsigned long lastActivity;

void parseNotificationCommand(String command);
void parseSpotifyCommand(String command);
void drawSpotifyScreen(Adafruit_ST7789 & tft, uint16_t color);
String getWiFiStatus();
void connectWiFi(String ssid, String password);
void handleWeatherCommand(String command);

void processCommand(String command);

#endif
