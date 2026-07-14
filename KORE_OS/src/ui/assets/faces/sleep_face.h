#pragma once

#include "face_utils.h"

unsigned long lastSleepAnim = 0;
unsigned long nextSleepAnim = 800;

int sleepFrame = 0;

// --------------------------------------------------
// SLEEP FACE
// --------------------------------------------------

void drawSleepFace(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  int ox = FACE_OX;
  int oy = FACE_OY;
  int s  = FACE_SPACING;

  // olho esquerdo fechado
  dot(tft, ox + 0*s, oy + 4*s, color);
  dot(tft, ox + 1*s, oy + 4*s, color);

  // olho direito fechado
  dot(tft, ox + 9*s, oy + 4*s, color);
  dot(tft, ox + 10*s, oy + 4*s, color);

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
// SLEEP LETTERS
// --------------------------------------------------

void clearSleepLetters(
  Adafruit_ST7789 &tft
)
{
  tft.fillRect(
    200,
    15,
    90,
    60,
    ST77XX_BLACK
  );
}

void drawSleepLetters(
  Adafruit_ST7789 &tft,
  uint16_t color,
  int frame
)
{
  clearSleepLetters(tft);

  tft.setTextColor(color);

  switch(frame)
  {
    case 1:

      tft.setTextSize(2);
      tft.setCursor(215, 50);
      tft.print("z");

      break;

    case 2:

      tft.setTextSize(2);
      tft.setCursor(215, 50);
      tft.print("z");

      tft.setTextSize(1);
      tft.setCursor(240, 38);
      tft.print("z");

      break;

    case 3:

      tft.setTextSize(2);
      tft.setCursor(215, 50);
      tft.print("z");

      tft.setTextSize(1);
      tft.setCursor(240, 38);
      tft.print("z");

      tft.setTextSize(2);
      tft.setCursor(255, 22);
      tft.print("z");

      break;
  }
}

// --------------------------------------------------
// ANIMATION
// --------------------------------------------------

void animateSleepFace(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  unsigned long now = millis();

  if(now - lastSleepAnim > nextSleepAnim)
  {
    sleepFrame++;

    if(sleepFrame > 3)
    {
      sleepFrame = 0;
    }

    drawSleepLetters(
      tft,
      color,
      sleepFrame
    );

    lastSleepAnim = now;

    nextSleepAnim = random(
      700,
      1400
    );
  }
}

// --------------------------------------------------
// SCREEN
// --------------------------------------------------

void drawSleepScreen(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  tft.fillScreen(
    ST77XX_BLACK
  );

  drawSleepFace(
    tft,
    color
  );

  sleepFrame = 0;

  drawSleepLetters(
    tft,
    color,
    sleepFrame
  );
}