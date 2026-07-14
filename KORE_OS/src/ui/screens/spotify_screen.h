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

extern bool spotifyActive;
extern unsigned long spotifyLastUpdate;

extern String spotifyTrack;
extern String spotifyArtist;
extern String spotifyAlbum;
extern long spotifyProgress;
extern long spotifyDuration;
extern unsigned long spotifyProgressSync;
extern int cassetteFrame;
extern unsigned long cassetteTimer;

extern unsigned long spotifyFaceTimer;

extern bool demonActive;
extern unsigned long demonStart;

// --------------------------------------------------
// WRAPPERS (Interface)
// --------------------------------------------------

void onEnterSpotify();
void updateSpotify();
void drawSpotifyScreen(Adafruit_ST7789 & tft, uint16_t color);
void renderSpotify();

// --------------------------------------------------
// DEMON MODE
// --------------------------------------------------

void updateDemonMode();

// --------------------------------------------------
// PARSE COMMAND
// --------------------------------------------------

void parseSpotifyCommand(String command);

// --------------------------------------------------
// DRAW BOBBIN
// --------------------------------------------------

void drawBobbin(Adafruit_ST7789 & tft, uint16_t color, int x, int y);

// --------------------------------------------------
// ANIMATION
// --------------------------------------------------

void animateSpotifyScreen(Adafruit_ST7789 & tft, uint16_t color);

// --------------------------------------------------
// TIME
// --------------------------------------------------

void drawSpotifyTime();

#endif
