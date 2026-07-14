#ifndef SPOTIFY_SCREEN_H
#define SPOTIFY_SCREEN_H

#include <Adafruit_ST7789.h>
#include <U8g2_for_Adafruit_GFX.h>
#include "../../config/display_context.h"
#include "../../managers/mood_manager.h"
#include "../../managers/demon_manager.h"

// --------------------------------------------------
// SPOTIFY DATA
// --------------------------------------------------

bool spotifyActive = false;
unsigned long spotifyLastUpdate = 0;

String spotifyTrack = "";
String spotifyArtist = "";
String spotifyAlbum = "";
long spotifyProgress = 0;
long spotifyDuration = 0;
unsigned long spotifyProgressSync = 0;
int cassetteFrame = 0;
unsigned long cassetteTimer = 0;

bool demonActive = false;
unsigned long demonStart = 0;

// --------------------------------------------------
// WRAPPERS (Interface)
// --------------------------------------------------

static bool spotifyShowingLove = false;
static unsigned long spotifyLoveStart = 0;
static bool spotifyNeedsRedraw = true;
static bool lovingScreenDrawn = false;
static unsigned long lastTimeDraw = 0;

void animateSpotifyScreen(Adafruit_ST7789 & tft, uint16_t color);
void drawSpotifyTime();
void updateDemonMode();

void onEnterSpotify() {
  spotifyNeedsRedraw = true;
  tft.fillScreen(ST77XX_BLACK);
}

void updateSpotify() {
  if (!spotifyActive)
    return;

  if (millis() - spotifyLastUpdate > 15000) {
    spotifyActive = false;
    setFace(faceBeforeSpotify);
    return;
  }

  unsigned long now = millis();

  if (spotifyShowingLove) {
    if (now - spotifyLoveStart >= 2000) {
      spotifyShowingLove = false;
      spotifyFaceTimer = now;
      spotifyNeedsRedraw = true;
      lovingScreenDrawn = false;
    }
    return;
  }

  if (now - spotifyFaceTimer >= 20000) {
    spotifyShowingLove = true;
    spotifyLoveStart = now;
    lovingScreenDrawn = false;
  }
  updateDemonMode();
}

void drawSpotifyScreen(
  Adafruit_ST7789 & tft,
  uint16_t color
);

void renderSpotify() {

  if (!spotifyActive)
    return;

  if (demonActive) {
    renderEmotion();
    return;
  }

  if (spotifyNeedsRedraw) {
    drawSpotifyScreen(tft, KORE_CYAN);
    spotifyNeedsRedraw = false;
  }

  if (spotifyShowingLove) {
    if (!lovingScreenDrawn) {
      drawLovingScreen(tft, KORE_CYAN);
      lovingScreenDrawn = true;
    }
    return;
  }

  if (
    millis() - lastTimeDraw >= 1000
  ) {
    drawSpotifyTime();
    lastTimeDraw = millis();
  }

  animateSpotifyScreen(
    tft,
    KORE_CYAN
  );
}

// --------------------------------------------------
// FORWARD DECLARATIONS
// --------------------------------------------------

void drawBobbin(
  Adafruit_ST7789 & tft,
  uint16_t color,
  int x,
  int y
);

void animateSpotifyScreen(
  Adafruit_ST7789 & tft,
  uint16_t color
);

// --------------------------------------------------
// DEMON MODE
// --------------------------------------------------

void updateDemonMode()
{
    if (!spotifyActive)
    {
        demonActive = false;
        demonTriggered = false;
        return;
    }

    if (!isDemonTrack(spotifyArtist, spotifyTrack))
    {
        if (demonActive)
        {
            demonActive = false;
            setFace(faceBeforeSpotify);
        }

        demonTriggered = false;
        return;
    }

    long currentProgress =
        spotifyProgress +
        (millis() - spotifyProgressSync);

    if (
        !demonTriggered &&
        currentProgress >= 66000
    )
    {
        demonTriggered = true;
        demonActive = true;
        demonStart = millis();

        setFace(FACE_DEMON);
    }

    if (
        demonActive &&
        millis() - demonStart >= 5000
    )
    {
        demonActive = false;

        setFace(faceBeforeSpotify);
    }
}

// --------------------------------------------------
// PARSE COMMAND
// --------------------------------------------------

void parseSpotifyCommand(
  String command
) {
  int p1 =
    command.indexOf('|');
  if (p1 < 0) return;

  int p2 =
    command.indexOf('|', p1 + 1);
  if (p2 < 0) return;

  int p3 =
    command.indexOf('|', p2 + 1);
  if (p3 < 0) return;

  int p4 =
    command.indexOf('|', p3 + 1);
  if (p4 < 0) return;

  int p5 =
    command.indexOf('|', p4 + 1);
  if (p5 < 0) return;

  int p6 =
    command.indexOf('|', p5 + 1);

  String previousTrack = spotifyTrack;
  String previousArtist = spotifyArtist;

  spotifyTrack =
    command.substring(
      p1 + 1,
      p2
    );

  spotifyArtist =
    command.substring(
      p2 + 1,
      p3
    );

  spotifyAlbum =
    command.substring(
      p3 + 1,
      p4
    );

  spotifyProgress =
    command.substring(
      p4 + 1,
      p5
    ).toInt();

  spotifyDuration =
    command.substring(
      p5 + 1,
      p6
    ).toInt();

  if (previousTrack != spotifyTrack || previousArtist != spotifyArtist) {
    demonTriggered = false;
    demonActive = false;
  }

  spotifyLastUpdate = millis();
  spotifyProgressSync = millis();
  spotifyActive = true;
  spotifyNeedsRedraw = true;
}

// --------------------------------------------------
// DRAW BOBBIN
// --------------------------------------------------

void drawBobbin(
  Adafruit_ST7789 & tft,
  uint16_t color,
  int x,
  int y
) {
  tft.fillCircle(
    x,
    y,
    18,
    ST77XX_BLACK
  );

  tft.drawCircle(
    x,
    y,
    20,
    color
  );

  tft.drawCircle(
    x,
    y,
    8,
    color
  );

  if (
    cassetteFrame == 0
  ) {
    tft.drawLine(
      x,
      y - 20,
      x,
      y - 8,
      color
    );

    tft.drawLine(
      x,
      y + 8,
      x,
      y + 20,
      color
    );

    tft.drawLine(
      x - 20,
      y,
      x - 8,
      y,
      color
    );

    tft.drawLine(
      x + 8,
      y,
      x + 20,
      y,
      color
    );
  } else {
    tft.drawLine(
      x - 14,
      y - 14,
      x - 6,
      y - 6,
      color
    );

    tft.drawLine(
      x + 6,
      y + 6,
      x + 14,
      y + 14,
      color
    );

    tft.drawLine(
      x + 14,
      y - 14,
      x + 6,
      y - 6,
      color
    );

    tft.drawLine(
      x - 14,
      y + 14,
      x - 6,
      y + 6,
      color
    );
  }
}

// --------------------------------------------------
// DRAW SCREEN
// --------------------------------------------------

void drawSpotifyScreen(
  Adafruit_ST7789 & tft,
  uint16_t color
) {
  tft.fillScreen(
    ST77XX_BLACK
  );

  // CASSETE

  tft.drawRoundRect(
    20,
    10,
    280,
    120,
    10,
    color
  );

  drawBobbin(
    tft,
    color,
    90,
    70
  );

  drawBobbin(
    tft,
    color,
    230,
    70
  );

  // JANELA

  tft.drawRect(
    130,
    48,
    60,
    36,
    color
  );

  // PROGRESSO
  long currentProgress = spotifyProgress + (millis() - spotifyProgressSync);

  if (currentProgress > spotifyDuration)
  {
    currentProgress = spotifyDuration;
  }

  int tapeWidth = 0;
  if (spotifyDuration > 0) {
    tapeWidth =
      map(
        currentProgress,
        0,
        spotifyDuration,
        0,
        56
      );
    tapeWidth = constrain(tapeWidth, 0, 56);
  }

  tft.fillRect(
    132,
    50,
    tapeWidth,
    32,
    color
  );

  // GUIA

  tft.drawLine(
    87,
    104,
    70,
    128,
    color
  );

  tft.drawLine(
    88,
    103,
    230,
    103,
    color
  );

  tft.drawLine(
    231,
    104,
    248,
    128,
    color
  );

  u8g2.setForegroundColor(
    color
  );

  // TRACK

  String track =
    spotifyTrack;

  if (
    track.length() > 24
  ) {
    track =
      track.substring(
        0,
        24
      );
  }

  u8g2.setFont(
    u8g2_font_helvB12_tf
  );

  u8g2.drawUTF8(
    20,
    160,
    track.c_str()
  );

  // ARTIST

  u8g2.setFont(
    u8g2_font_helvB10_tf
  );

  u8g2.drawUTF8(
    20,
    190,
    spotifyArtist.c_str()
  );

  // TEMPO
  drawSpotifyTime();
}

void drawSpotifyTime()
{
  long currentProgress =
    spotifyProgress +
    (millis() - spotifyProgressSync);

  if(currentProgress > spotifyDuration)
  {
    currentProgress = spotifyDuration;
  }

  long currentSeconds =
    currentProgress / 1000;

  long totalSeconds =
    spotifyDuration / 1000;

  char timeBuffer[32];

  sprintf(
    timeBuffer,
    "%02ld:%02ld / %02ld:%02ld",
    currentSeconds / 60,
    currentSeconds % 60,
    totalSeconds / 60,
    totalSeconds % 60
  );

  // limpa somente a área do contador

  tft.fillRect(
    20,
    198,
    220,
    24,
    ST77XX_BLACK
  );
  u8g2.setForegroundColor(KORE_CYAN);
  u8g2.setFont(u8g2_font_helvB10_tf);

  u8g2.drawUTF8(
    20,
    215,
    timeBuffer
  );
}

// --------------------------------------------------
// ANIMATION
// --------------------------------------------------

void animateSpotifyScreen(
  Adafruit_ST7789 & tft,
  uint16_t color
) {
  if (
    millis() - cassetteTimer < 250
  ) {
    return;
  }

  cassetteTimer =
    millis();

  cassetteFrame = !cassetteFrame;

  drawBobbin(
    tft,
    color,
    90,
    70
  );

  drawBobbin(
    tft,
    color,
    230,
    70
  );
}

#endif