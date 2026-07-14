#ifndef MOOD_MANAGER_H
#define MOOD_MANAGER_H

#include <Arduino.h>

#include "../config/display_context.h"

// --------------------------------------------------
// FACE TYPES
// --------------------------------------------------

enum FaceType {
  FACE_HAPPY,
  FACE_EXTRA_HAPPY,
  FACE_SAD,
  FACE_SLEEP,
  FACE_SURPRISE,
  FACE_LOVING,
  FACE_CONFUSED,
  FACE_DEMON
};

// --------------------------------------------------
// EXTERNAL VARIABLES (Defined in KORE_OS.ino)
// --------------------------------------------------

extern FaceType currentFace;
extern FaceType defaultFace;
extern FaceType faceBeforeSpotify;
extern unsigned long spotifyFaceTimer;

// --------------------------------------------------
// FORWARD DECLARATIONS (Drawing and Animate functions)
// --------------------------------------------------

void drawHappyScreen(Adafruit_ST7789 & tft, uint16_t color);
void drawExtraHappyScreen(Adafruit_ST7789 & tft, uint16_t color);
void drawSadScreen(Adafruit_ST7789 & tft, uint16_t color);
void drawSleepScreen(Adafruit_ST7789 & tft, uint16_t color);
void drawSurpriseScreen(Adafruit_ST7789 & tft, uint16_t color);
void drawLovingScreen(Adafruit_ST7789 & tft, uint16_t color);
void drawDemonScreen(Adafruit_ST7789 & tft, uint16_t color);
void drawConfusedScreen(Adafruit_ST7789 & tft, uint16_t color);

void animateHappyFace(Adafruit_ST7789 & tft, uint16_t color);
void animateExtraHappyFace(Adafruit_ST7789 & tft, uint16_t color);
void animateSadFace(Adafruit_ST7789 & tft, uint16_t color);
void animateSleepFace(Adafruit_ST7789 & tft, uint16_t color);
void animateSurpriseFace(Adafruit_ST7789 & tft, uint16_t color);
void animateLovingFace(Adafruit_ST7789 & tft, uint16_t color);
void animateDemonFace(Adafruit_ST7789 & tft, uint16_t color);
void animateConfusedFace(Adafruit_ST7789 & tft, uint16_t color);

// --------------------------------------------------
// WRAPPERS (Interface)
// --------------------------------------------------

void onEnterEmotion() {
  tft.fillScreen(ST77XX_BLACK);
}

void updateEmotion() {
  // Lógica de blink, etc.
}

void renderEmotion() {
  switch (currentFace) {

  case FACE_HAPPY:
    animateHappyFace(
      tft,
      KORE_CYAN
    );
    break;

  case FACE_EXTRA_HAPPY:
    animateExtraHappyFace(
      tft,
      KORE_CYAN
    );
    break;

  case FACE_SAD:
    animateSadFace(
      tft,
      KORE_CYAN
    );
    break;

  case FACE_SLEEP:
    animateSleepFace(
      tft,
      KORE_CYAN
    );
    break;

  case FACE_SURPRISE:
    animateSurpriseFace(
      tft,
      KORE_CYAN
    );
    break;

  case FACE_LOVING:
    animateLovingFace(
      tft,
      KORE_CYAN
    );
    break;

  case FACE_CONFUSED:
    animateConfusedFace(
      tft,
      KORE_CYAN
    );
    break;

  case FACE_DEMON:
    animateDemonFace(
      tft,
      ST77XX_RED
    );
    break;
  }
}

// --------------------------------------------------
// SET FACE
// --------------------------------------------------

void setFace(FaceType face) {

  currentFace = face;

  switch (currentFace) {

  case FACE_HAPPY:
    drawHappyScreen(
      tft,
      KORE_CYAN
    );
    break;

  case FACE_EXTRA_HAPPY:
    drawExtraHappyScreen(
      tft,
      KORE_CYAN
    );
    break;

  case FACE_SAD:
    drawSadScreen(
      tft,
      KORE_CYAN
    );
    break;

  case FACE_SLEEP:
    drawSleepScreen(
      tft,
      KORE_CYAN
    );
    break;

  case FACE_SURPRISE:
    drawSurpriseScreen(
      tft,
      KORE_CYAN
    );
    break;

  case FACE_LOVING:
    drawLovingScreen(
      tft,
      KORE_CYAN
    );
    break;

  case FACE_CONFUSED:
    drawConfusedScreen(
      tft,
      KORE_CYAN
    );
    break;

  case FACE_DEMON:
    drawDemonScreen(
      tft,
      ST77XX_RED
    );
    break;
  }
}

// --------------------------------------------------
// CURRENT FACE NAME
// --------------------------------------------------

String getCurrentFaceName() {

  switch (currentFace) {

  case FACE_HAPPY:
    return "happy";

  case FACE_EXTRA_HAPPY:
    return "extrahappy";

  case FACE_SAD:
    return "sad";

  case FACE_SLEEP:
    return "sleep";

  case FACE_SURPRISE:
    return "surprise";

  case FACE_LOVING:
    return "loving";

  case FACE_CONFUSED:
    return "confused";

  case FACE_DEMON:
    return "demon";
  }

  return "unknown";
}

#endif