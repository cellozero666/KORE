#pragma once

#include <Adafruit_ST7789.h>
#include "../assets/cat.h"

void drawProgressBar(Adafruit_ST7789 &tft, int progress, uint16_t color);
void bootScreen(Adafruit_ST7789 &tft, uint16_t color);
void initBootAnimation();
bool updateBootAnimation();
