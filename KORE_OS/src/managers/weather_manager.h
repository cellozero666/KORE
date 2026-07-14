#ifndef WEATHER_MANAGER_H
#define WEATHER_MANAGER_H

#include <Adafruit_ST7789.h>
#include <U8g2_for_Adafruit_GFX.h>
#include "../ui/assets/weather_icons.h"
#include "../config/display_context.h"
#include "../config/config.h"

// --------------------------------------------------
// DATA STRUCTURES
// --------------------------------------------------

struct WeatherData {
  int temperature;
  int highTemp;
  int lowTemp;
  String city;
  WIconIndex icon;
  unsigned long lastUpdate;
};

// --------------------------------------------------
// GLOBALS
// --------------------------------------------------

extern WeatherData currentWeather;
extern bool weatherActive;
extern unsigned long weatherStartTime;

// --------------------------------------------------
// INTERNAL DRAW
// --------------------------------------------------

void drawWeatherScreen() {

  tft.fillScreen(ST77XX_BLACK);

  u8g2.setForegroundColor(KORE_CYAN);

  // Título
  u8g2.setFont(u8g2_font_helvB12_tf);
  u8g2.drawUTF8(
    (SCREEN_WIDTH - u8g2.getUTF8Width("WEATHER")) / 2,
    30,
    "WEATHER"
  );

  // Ícone
  tft.drawBitmap(
    (SCREEN_WIDTH - 64) / 2,
    50,
    weatherIcons[currentWeather.icon],
    64,
    64,
    KORE_CYAN
  );

  // Temperatura
  u8g2.setFont(u8g2_font_helvB24_tf);

  String tempStr =
    String(currentWeather.temperature) + "C";

  u8g2.drawUTF8(
    (SCREEN_WIDTH - u8g2.getUTF8Width(tempStr.c_str())) / 2,
    140,
    tempStr.c_str()
  );

  // Cidade
  u8g2.setFont(u8g2_font_helvB12_tf);

  u8g2.drawUTF8(
    (SCREEN_WIDTH - u8g2.getUTF8Width(currentWeather.city.c_str())) / 2,
    180,
    currentWeather.city.c_str()
  );

  // Máxima / mínima
  String rangeStr =
    "H:" + String(currentWeather.highTemp) +
    "  L:" + String(currentWeather.lowTemp);

  u8g2.drawUTF8(
    (SCREEN_WIDTH - u8g2.getUTF8Width(rangeStr.c_str())) / 2,
    210,
    rangeStr.c_str()
  );
}

// --------------------------------------------------
// DISPLAY MANAGER INTERFACE
// --------------------------------------------------

void onEnterWeather() {
  drawWeatherScreen();
}

void updateWeather() {

  if (
    weatherActive &&
    millis() - weatherStartTime >= 15000
  ) {
    weatherActive = false;
  }
}

void renderWeather() {
  // NÃO redesenhar continuamente
}

// --------------------------------------------------
// COMMAND PARSING
// --------------------------------------------------

void handleWeatherCommand(String command) {

  if (!command.startsWith("weather|"))
    return;

  int p[5];

  p[0] = command.indexOf('|');
  if (p[0] < 0) return;

  p[1] = command.indexOf('|', p[0] + 1);
  if (p[1] < 0) return;

  p[2] = command.indexOf('|', p[1] + 1);
  if (p[2] < 0) return;

  p[3] = command.indexOf('|', p[2] + 1);
  if (p[3] < 0) return;

  p[4] = command.indexOf('|', p[3] + 1);
  if (p[4] < 0) return;

  currentWeather.city =
    command.substring(p[0] + 1, p[1]);

  currentWeather.temperature =
    command.substring(p[1] + 1, p[2]).toInt();

  currentWeather.highTemp =
    command.substring(p[2] + 1, p[3]).toInt();

  currentWeather.lowTemp =
    command.substring(p[3] + 1, p[4]).toInt();

  currentWeather.icon =
    (WIconIndex)command.substring(p[4] + 1).toInt();

  currentWeather.lastUpdate =
    millis();

  weatherActive = true;
  weatherStartTime = millis();

  // força redesenho imediato quando chegar novo clima
  drawWeatherScreen();
}

#endif