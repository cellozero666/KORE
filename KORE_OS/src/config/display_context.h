#ifndef DISPLAY_CONTEXT_H
#define DISPLAY_CONTEXT_H

#include <Adafruit_ST7789.h>
#include <U8g2_for_Adafruit_GFX.h>

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

extern Adafruit_ST7789 tft;
extern U8G2_FOR_ADAFRUIT_GFX u8g2;
extern uint16_t KORE_CYAN;

#endif
