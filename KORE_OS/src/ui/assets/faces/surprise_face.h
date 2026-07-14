#pragma once

#include "face_utils.h"

// --------------------------------------------------
// SURPRISE FACE
// --------------------------------------------------

void drawSurpriseFace(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  int ox = FACE_OX;
  int oy = FACE_OY;
  int s  = FACE_SPACING;

  // olho esquerdo
  dot(tft, ox + 0*s, oy + 2*s, color);
  dot(tft, ox + 1*s, oy + 2*s, color);

  dot(tft, ox + 0*s, oy + 3*s, color);
  dot(tft, ox + 1*s, oy + 3*s, color);

  dot(tft, ox + 0*s, oy + 4*s, color);
  dot(tft, ox + 1*s, oy + 4*s, color);

  dot(tft, ox + 0*s, oy + 5*s, color);
  dot(tft, ox + 1*s, oy + 5*s, color);

  // olho direito
  dot(tft, ox + 9*s, oy + 2*s, color);
  dot(tft, ox + 10*s, oy + 2*s, color);

  dot(tft, ox + 9*s, oy + 3*s, color);
  dot(tft, ox + 10*s, oy + 3*s, color);

  dot(tft, ox + 9*s, oy + 4*s, color);
  dot(tft, ox + 10*s, oy + 4*s, color);

  dot(tft, ox + 9*s, oy + 5*s, color);
  dot(tft, ox + 10*s, oy + 5*s, color);

  // boca surpresa

  

  dot(tft, ox + 4*s, oy + 11*s, color);
  dot(tft, ox + 5*s, oy + 11*s, color);

  dot(tft, ox + 4*s, oy + 12*s, color);
  dot(tft, ox + 5*s, oy + 12*s, color);
}

// --------------------------------------------------
// ANIMATION
// --------------------------------------------------

void animateSurpriseFace(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  unsigned long now = millis();

  if (!blinkPhase)
  {
    if (now - lastBlink >= nextBlink)
    {
      drawBlinkEyes(
        tft,
        color
      );

      blinkPhase = true;
      blinkStart = now;
    }
  }
  else if (now - blinkStart >= 100)
  {
    drawSurpriseFace(
      tft,
      color
    );

    lastBlink = now;

    nextBlink = random(
      BLINK_INTERVAL_MIN,
      BLINK_INTERVAL_MAX
    );

    blinkPhase = false;
  }
}

// --------------------------------------------------
// SCREEN
// --------------------------------------------------

void drawSurpriseScreen(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  tft.fillScreen(
    ST77XX_BLACK
  );

  drawSurpriseFace(
    tft,
    color
  );
}