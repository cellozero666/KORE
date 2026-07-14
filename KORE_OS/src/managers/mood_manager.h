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
extern bool faceNeedsRedraw;

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
// WRAPPERS (Interface) - Declarations only
// --------------------------------------------------

void onEnterEmotion();
void updateEmotion();
void renderEmotion();
void setFace(FaceType face);
String getCurrentFaceName();
void resetFaceAnimationState();

#endif