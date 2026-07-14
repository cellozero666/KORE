#pragma once

#include "face_utils.h"

// --------------------------------------------------
// LOVING FACE
// --------------------------------------------------

void drawHeart(
  Adafruit_ST7789 &tft,
  int x,
  int y,
  int s,
  uint16_t color
)
{
  dot(tft, x + 0*s, y + 0*s, color);
  dot(tft, x + 1*s, y + 0*s, color);

  dot(tft, x + 3*s, y + 0*s, color);
  dot(tft, x + 4*s, y + 0*s, color);

  for(int i = 0; i <= 4; i++)
  {
    dot(tft, x + i*s, y + 1*s, color);
  }

  for(int i = 0; i <= 4; i++)
  {
    dot(tft, x + i*s, y + 2*s, color);
  }

  dot(tft, x + 1*s, y + 3*s, color);
  dot(tft, x + 2*s, y + 3*s, color);
  dot(tft, x + 3*s, y + 3*s, color);

  dot(tft, x + 2*s, y + 4*s, color);
}

void clearHearts(
  Adafruit_ST7789 &tft
)
{
  int ox = FACE_OX;
  int oy = FACE_OY;

  tft.fillRect(
    ox - 10,
    oy,
    170,
    60,
    ST77XX_BLACK
  );
}

void drawLovingFace(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  int ox = 95;
  int oy = 45;

  int heartSpacing = 7;

  // coração esquerdo

  drawHeart(
    tft,
    ox,
    oy + 15,
    heartSpacing,
    color
  );

  // coração direito

  drawHeart(
    tft,
    ox + 14 * heartSpacing,
    oy + 15,
    heartSpacing,
    color
  );

  // boca esquerda

  dot(tft, ox + 0*12, oy + 9*12, color);
  dot(tft, ox + 1*12, oy + 9*12, color);

  dot(tft, ox + 0*12, oy + 10*12, color);
  dot(tft, ox + 1*12, oy + 10*12, color);

  // boca direita

  dot(tft, ox + 9*12, oy + 9*12, color);
  dot(tft, ox + 10*12, oy + 9*12, color);

  dot(tft, ox + 9*12, oy + 10*12, color);
  dot(tft, ox + 10*12, oy + 10*12, color);

  // sorriso

  for(int i = 2; i <= 8; i++)
  {
    dot(
      tft,
      ox + i*12,
      oy + 11*12,
      color
    );

    dot(
      tft,
      ox + i*12,
      oy + 12*12,
      color
    );
  }
}

// --------------------------------------------------
// ANIMATION
// --------------------------------------------------

void animateLovingFace(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  unsigned long now = millis();

  if (!blinkPhase)
  {
    if (now - lastBlink >= nextBlink)
    {
      clearHearts(
        tft
      );

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
    drawLovingFace(
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

void drawLovingScreen(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  tft.fillScreen(
    ST77XX_BLACK
  );

  drawLovingFace(
    tft,
    color
  );
}