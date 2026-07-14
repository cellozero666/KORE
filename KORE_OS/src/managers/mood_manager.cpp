#include "mood_manager.h"
#include "../config/display_context.h"
#include "../ui/assets/faces/happy_face.h"
#include "../ui/assets/faces/extra_happy_face.h"
#include "../ui/assets/faces/sad_face.h"
#include "../ui/assets/faces/sleep_face.h"
#include "../ui/assets/faces/surprise_face.h"
#include "../ui/assets/faces/loving_face.h"
#include "../ui/assets/faces/confused_face.h"
#include "../ui/assets/faces/demon_face.h"

// --------------------------------------------------
// WRAPPERS (Interface)
// --------------------------------------------------

bool faceNeedsRedraw = true;

void onEnterEmotion() {
  tft.fillScreen(ST77XX_BLACK);
  faceNeedsRedraw = true;
}

void updateEmotion() {
  // Lógica de blink, etc.
}

void renderEmotion() {
  if (faceNeedsRedraw)
  {
    faceNeedsRedraw = false;

    switch (currentFace) {

    case FACE_HAPPY:
      drawHappyScreen(tft, KORE_CYAN);
      break;

    case FACE_EXTRA_HAPPY:
      drawExtraHappyScreen(tft, KORE_CYAN);
      break;

    case FACE_SAD:
      drawSadScreen(tft, KORE_CYAN);
      break;

    case FACE_SLEEP:
      drawSleepScreen(tft, KORE_CYAN);
      break;

    case FACE_SURPRISE:
      drawSurpriseScreen(tft, KORE_CYAN);
      break;

    case FACE_LOVING:
      drawLovingScreen(tft, KORE_CYAN);
      break;

    case FACE_CONFUSED:
      drawConfusedScreen(tft, KORE_CYAN);
      break;

    case FACE_DEMON:
      drawDemonScreen(tft, ST77XX_RED);
      break;

    default:
      break;
    }
    return;
  }

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

  default:
    break;
  }
}

// --------------------------------------------------
// RESET FACE ANIMATION STATE
// --------------------------------------------------

void resetFaceAnimationState() {
    lastBlink = 0;
    nextBlink = 2500;
    blinkStart = 0;
    blinkPhase = false;

    lastSleepAnim = 0;
    nextSleepAnim = 800;
    sleepFrame = 0;
}

// --------------------------------------------------
// SET FACE
// --------------------------------------------------

void setFace(FaceType face) {
    resetFaceAnimationState();

    faceNeedsRedraw = false;

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

  default:
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

  default:
    return "unknown";
  }
}
