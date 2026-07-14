#pragma once

#include "face_utils.h"

// --------------------------------------------------
// HAPPY FACE
// --------------------------------------------------

void drawExtraHappyFace(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  int ox = FACE_OX;
  int oy = FACE_OY;
  int s  = FACE_SPACING;

  // --------------------------------------------------
  // OLHO ESQUERDO
  // --------------------------------------------------

  for(int y = 2; y <= 5; y++)
  {
    dot(tft, ox + 0*s, oy + y*s, color);
    dot(tft, ox + 1*s, oy + y*s, color);
  }

  // --------------------------------------------------
  // OLHO DIREITO
  // --------------------------------------------------

  for(int y = 2; y <= 5; y++)
  {
    dot(tft, ox + 9*s,  oy + y*s, color);
    dot(tft, ox + 10*s, oy + y*s, color);
  }

  // --------------------------------------------------
  // BOCA ESQUERDA
  // --------------------------------------------------

  for(int x = 0; x <= 7; x += 2)
  {
    dot(tft, ox + x*s,     oy + 9*s,  color);
    dot(tft, ox + (x+1)*s, oy + 9*s,  color);

    dot(tft, ox + x*s,     oy + 10*s, color);
    dot(tft, ox + (x+1)*s, oy + 10*s, color);
  }

  dot(tft, ox + 8*s, oy + 9*s, color);
  dot(tft, ox + 8*s, oy + 10*s, color);

  dot(tft, ox + 1*s, oy + 11*s, color);

  // --------------------------------------------------
  // BOCA DIREITA
  // --------------------------------------------------

  dot(tft, ox + 9*s,  oy + 9*s,  color);
  dot(tft, ox + 10*s, oy + 9*s,  color);

  dot(tft, ox + 9*s,  oy + 10*s, color);
  dot(tft, ox + 10*s, oy + 10*s, color);

  dot(tft, ox + 9*s, oy + 11*s, color);

  // --------------------------------------------------
  // SORRISO
  // --------------------------------------------------

  for(int i = 2; i <= 8; i++)
  {
    dot(tft, ox + i*s, oy + 11*s, color);
    dot(tft, ox + i*s, oy + 12*s, color);
  }
}

// --------------------------------------------------
// ANIMATION
// --------------------------------------------------

void animateExtraHappyFace(
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
  else if (now - blinkStart >= BLINK_DELAY_MS)
  {
    drawExtraHappyFace(
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

void drawExtraHappyScreen(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  tft.fillScreen(
    ST77XX_BLACK
  );

  drawExtraHappyFace(
    tft,
    color
  );
}