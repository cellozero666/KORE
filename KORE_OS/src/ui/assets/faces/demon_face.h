#pragma once

#include "face_utils.h"

// --------------------------------------------------
// GLITCH
// --------------------------------------------------

unsigned long lastGlitch = 0;
unsigned long nextGlitch = 500;

// --------------------------------------------------
// DEMON FACE
// --------------------------------------------------

void drawDemonFace(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  int ox = FACE_OX;
  int oy = FACE_OY;
  int s  = FACE_SPACING;

  // -------------------------
  // OLHO ESQUERDO
  // -------------------------

  dot(tft, ox + 0*s, oy + 2*s, color);
  dot(tft, ox + 1*s, oy + 2*s, color);

  dot(tft, ox + 1*s, oy + 3*s, color);
  dot(tft, ox + 2*s, oy + 3*s, color);

  dot(tft, ox + 2*s, oy + 4*s, color);
  dot(tft, ox + 3*s, oy + 4*s, color);

  dot(tft, ox + 3*s, oy + 5*s, color);
  dot(tft, ox + 4*s, oy + 5*s, color);

  // -------------------------
  // OLHO DIREITO
  // -------------------------

  dot(tft, ox + 6*s, oy + 5*s, color);
  dot(tft, ox + 7*s, oy + 5*s, color);

  dot(tft, ox + 7*s, oy + 4*s, color);
  dot(tft, ox + 8*s, oy + 4*s, color);

  dot(tft, ox + 8*s, oy + 3*s, color);
  dot(tft, ox + 9*s, oy + 3*s, color);

  dot(tft, ox + 9*s, oy + 2*s, color);
  dot(tft, ox + 10*s, oy + 2*s, color);

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
// SCREEN
// --------------------------------------------------

void drawDemonScreen(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  tft.fillScreen(
    ST77XX_BLACK
  );

  drawDemonFace(
    tft,
    color
  );
}

// --------------------------------------------------
// ANIMATION
// --------------------------------------------------

void animateDemonFace(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  unsigned long now = millis();

  if (now - lastGlitch > nextGlitch)
  {
    for (int i = 0; i < 3; i++)
    {
      tft.fillRect(
        0,
        random(40, 220),
        240,
        4,
        ST77XX_RED
      );
    }

    delay(20);

    drawDemonScreen(
      tft,
      color
    );

    lastGlitch = now;

    nextGlitch = random(
      200,
      800
    );
  }
}