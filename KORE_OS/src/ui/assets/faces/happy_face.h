#pragma once

#include "face_utils.h"

// --------------------------------------------------
// HAPPY FACE
// --------------------------------------------------

void drawHappyFace(
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

  // boca esquerda
  dot(tft, ox + 0*s, oy + 9*s, color);
  dot(tft, ox + 1*s, oy + 9*s, color);

  dot(tft, ox + 0*s, oy + 10*s, color);
  dot(tft, ox + 1*s, oy + 10*s, color);

  // boca direita
  dot(tft, ox + 9*s, oy + 9*s, color);
  dot(tft, ox + 10*s, oy + 9*s, color);

  dot(tft, ox + 9*s, oy + 10*s, color);
  dot(tft, ox + 10*s, oy + 10*s, color);

  // sorriso
  for(int i = 2; i <= 8; i++)
  {
    dot(
      tft,
      ox + i*s,
      oy + 11*s,
      color
    );

    dot(
      tft,
      ox + i*s,
      oy + 12*s,
      color
    );
  }
}

// --------------------------------------------------
// ANIMATION
// --------------------------------------------------

void animateHappyFace(
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
    drawHappyFace(
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

void drawHappyScreen(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  tft.fillScreen(
    ST77XX_BLACK
  );

  drawHappyFace(
    tft,
    color
  );
}