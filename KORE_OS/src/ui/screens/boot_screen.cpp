#include "boot_screen.h"
#include <Arduino.h>
#include "../../config/display_context.h"

static int bootProgress = 0;
static unsigned long bootLastStep = 0;
static bool bootFinalDelay = false;
static unsigned long bootFinalStart = 0;
static bool bootAnimationComplete = false;

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

  drawProgressBar(
    tft,
    0,
    color
  );
}

void initBootAnimation()
{
  bootProgress = 0;
  bootLastStep = 0;
  bootFinalDelay = false;
  bootFinalStart = 0;
  bootAnimationComplete = false;
}

bool updateBootAnimation()
{
  if (bootAnimationComplete) return true;

  unsigned long now = millis();

  if (!bootFinalDelay)
  {
    if (now - bootLastStep >= 25)
    {
      bootLastStep = now;
      bootProgress += 4;
      if (bootProgress > 196) bootProgress = 196;
      drawProgressBar(
        tft,
        bootProgress,
        KORE_CYAN
      );
      if (bootProgress >= 196)
      {
        bootFinalDelay = true;
        bootFinalStart = now;
      }
    }
  }
  else
  {
    if (now - bootFinalStart >= 1000)
    {
      bootAnimationComplete = true;
      return true;
    }
  }

  return false;
}
