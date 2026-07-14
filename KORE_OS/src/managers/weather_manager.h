#ifndef WEATHER_MANAGER_H
#define WEATHER_MANAGER_H

#include <Adafruit_ST7789.h>
#include <U8g2_for_Adafruit_GFX.h>
#include "../ui/assets/weather_icons.h"
#include "../config/config.h"

struct WeatherData {
  int temperature;
  int highTemp;
  int lowTemp;
  String city;
  WIconIndex icon;
  unsigned long lastUpdate;
};

extern WeatherData currentWeather;
extern bool weatherActive;
extern unsigned long weatherStartTime;

void drawWeatherScreen();
void onEnterWeather();
void updateWeather();
void renderWeather();
void handleWeatherCommand(String command);

#endif
