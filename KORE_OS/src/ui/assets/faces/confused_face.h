#pragma once

#include "face_utils.h"

// --------------------------------------------------
// QUESTIONS
// --------------------------------------------------

unsigned long lastQuestion = 0;
unsigned long nextQuestion = 800;

bool questionVisible = false;

int questionX = 0;
int questionY = 0;
int questionSize = 2;

// --------------------------------------------------
// QUESTION MARK
// --------------------------------------------------

void drawQuestionMark(
  Adafruit_ST7789 &tft,
  int x,
  int y,
  int size,
  uint16_t color
)
{
  tft.setTextColor(color);
  tft.setTextSize(size);
  tft.setCursor(x, y);
  tft.print("?");
}

void clearQuestionMark(
  Adafruit_ST7789 &tft,
  int x,
  int y,
  int size
)
{
  int w = 12 * size;
  int h = 16 * size;

  tft.fillRect(
    x - 4,
    y - 4,
    w + 8,
    h + 8,
    ST77XX_BLACK
  );
}

// --------------------------------------------------
// CONFUSED FACE
// --------------------------------------------------

void drawConfusedFace(
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

  // olho direito (mais alto)

  dot(tft, ox + 9*s, oy + 1*s, color);
  dot(tft, ox + 10*s, oy + 1*s, color);

  dot(tft, ox + 9*s, oy + 2*s, color);
  dot(tft, ox + 10*s, oy + 2*s, color);

  dot(tft, ox + 9*s, oy + 3*s, color);
  dot(tft, ox + 10*s, oy + 3*s, color);

  dot(tft, ox + 9*s, oy + 4*s, color);
  dot(tft, ox + 10*s, oy + 4*s, color);

  // boca esquerda

  dot(tft, ox + 0*s, oy + 10*s, color);
  dot(tft, ox + 1*s, oy + 10*s, color);

  dot(tft, ox + 0*s, oy + 11*s, color);
  dot(tft, ox + 1*s, oy + 11*s, color);

  // boca reta

  for(int i = 2; i <= 8; i++)
  {
    dot(tft, ox + i*s, oy + 11*s, color);
    dot(tft, ox + i*s, oy + 12*s, color);
  }

  // boca direita

  dot(tft, ox + 9*s, oy + 10*s, color);
  dot(tft, ox + 10*s, oy + 10*s, color);

  dot(tft, ox + 9*s, oy + 11*s, color);
  dot(tft, ox + 10*s, oy + 11*s, color);
}

// --------------------------------------------------
// ANIMATION
// --------------------------------------------------

void animateConfusedFace(
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
    drawConfusedFace(
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

  // questions

  if(now - lastQuestion > nextQuestion)
  {
    if(questionVisible)
    {
      clearQuestionMark(
        tft,
        questionX,
        questionY,
        questionSize
      );

      drawConfusedFace(
        tft,
        color
      );

      questionVisible = false;

      nextQuestion = random(
        150,
        500
      );
    }
    else
    {
      questionSize = random(
        2,
        6
      );

      // lado esquerdo ou direito

      if(random(0, 2))
      {
        questionX = random(
          5,
          50
        );
      }
      else
      {
        questionX = random(
          180,
          215
        );
      }

      questionY = random(
        10,
        160
      );

      drawQuestionMark(
        tft,
        questionX,
        questionY,
        questionSize,
        color
      );

      questionVisible = true;

      nextQuestion = random(
        300,
        1000
      );
    }

    lastQuestion = now;
  }
}

// --------------------------------------------------
// SCREEN
// --------------------------------------------------

void drawConfusedScreen(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  tft.fillScreen(
    ST77XX_BLACK
  );

  drawConfusedFace(
    tft,
    color
  );
}