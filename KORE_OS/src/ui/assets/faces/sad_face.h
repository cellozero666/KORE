#pragma once

#include "face_utils.h"

// --------------------------------------------------
// SAD FACE
// --------------------------------------------------

void drawSadFace(
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

  // canto esquerdo da boca
  dot(tft, ox + 0*s, oy + 11*s, color);
  dot(tft, ox + 1*s, oy + 11*s, color);

  dot(tft, ox + 0*s, oy + 12*s, color);
  dot(tft, ox + 1*s, oy + 12*s, color);

  // canto direito da boca
  dot(tft, ox + 9*s, oy + 11*s, color);
  dot(tft, ox + 10*s, oy + 11*s, color);

  dot(tft, ox + 9*s, oy + 12*s, color);
  dot(tft, ox + 10*s, oy + 12*s, color);

  // linha triste
  for(int i = 2; i <= 8; i++)
  {
    dot(
      tft,
      ox + i*s,
      oy + 10*s,
      color
    );

    dot(
      tft,
      ox + i*s,
      oy + 11*s,
      color
    );
  }
}

// --------------------------------------------------
// ANIMATION
// --------------------------------------------------

void animateSadFace(
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
    drawSadFace(
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

void drawSadScreen(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  tft.fillScreen(
    ST77XX_BLACK
  );

  drawSadFace(
    tft,
    color
  );
}