#pragma once

#include "../assets/cat.h"

// --------------------------------------------------
// PROGRESS BAR
// --------------------------------------------------

void drawProgressBar(
  Adafruit_ST7789 &tft,
  int progress,
  uint16_t color
)
{
  tft.drawRect(
    60,
    220,
    200,
    16,
    color
  );

  tft.fillRect(
    62,
    222,
    progress,
    12,
    color
  );
}

// --------------------------------------------------
// BOOT SCREEN
// --------------------------------------------------

void bootScreen(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  tft.fillScreen(
    ST77XX_BLACK
  );

  tft.drawBitmap(
    110,
    20,
    catBitmap,
    CAT_WIDTH,
    CAT_HEIGHT,
    color
  );

  tft.setTextColor(
    color
  );

  tft.setTextSize(3);

  tft.setCursor(
    90,
    125
  );

  tft.print("K.O.R.E.");

  tft.setCursor(
    130,
    155
  );

  tft.print("O S");

  tft.setTextSize(1);

  tft.setCursor(
    105,
    190
  );

  tft.print("Starting system");

  for(int i = 0; i <= 196; i += 4)
  {
    drawProgressBar(
      tft,
      i,
      color
    );

    delay(25);
  }

  delay(1000);
}