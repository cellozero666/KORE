#pragma once

// --------------------------------------------------
// FACE CONFIG
// --------------------------------------------------

#define FACE_OX       95
#define FACE_OY       45
#define FACE_SPACING  12

#define FACE_DOT_SIZE 3

// --------------------------------------------------
// BLINK
// --------------------------------------------------

#define BLINK_DELAY_MS     120
#define BLINK_INTERVAL_MIN 2000
#define BLINK_INTERVAL_MAX 5000

unsigned long lastBlink = 0;
unsigned long nextBlink = 2500;
unsigned long blinkStart = 0;
bool blinkPhase = false;

// --------------------------------------------------
// PIXELS
// --------------------------------------------------

void dot(
  Adafruit_ST7789 &tft,
  int x,
  int y,
  uint16_t color
)
{
  tft.fillCircle(
    x,
    y,
    FACE_DOT_SIZE,
    color
  );
}

void clearDot(
  Adafruit_ST7789 &tft,
  int x,
  int y
)
{
  tft.fillCircle(
    x,
    y,
    FACE_DOT_SIZE + 1,
    ST77XX_BLACK
  );
}

// --------------------------------------------------
// BLINK
// --------------------------------------------------

void drawBlinkEyes(
  Adafruit_ST7789 &tft,
  uint16_t color
)
{
  int ox = FACE_OX;
  int oy = FACE_OY;
  int s  = FACE_SPACING;

  // apagar olho esquerdo

  for(int y = 2; y <= 5; y++)
  {
    clearDot(
      tft,
      ox + 0*s,
      oy + y*s
    );

    clearDot(
      tft,
      ox + 1*s,
      oy + y*s
    );
  }

  // apagar olho direito

  for(int y = 2; y <= 5; y++)
  {
    clearDot(
      tft,
      ox + 9*s,
      oy + y*s
    );

    clearDot(
      tft,
      ox + 10*s,
      oy + y*s
    );
  }

  // olhos fechados

  dot(
    tft,
    ox + 0*s,
    oy + 4*s,
    color
  );

  dot(
    tft,
    ox + 1*s,
    oy + 4*s,
    color
  );

  dot(
    tft,
    ox + 9*s,
    oy + 4*s,
    color
  );

  dot(
    tft,
    ox + 10*s,
    oy + 4*s,
    color
  );
}