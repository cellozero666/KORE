#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <U8g2_for_Adafruit_GFX.h>
#include <SPI.h>
#include <pgmspace.h>

#include "src/managers/output_manager.h"
#include "src/core/command_parser.h"
#include "src/config/config.h"
#include "src/ui/screens/boot_screen.h"
#include "src/ui/screens/spotify_screen.h"
#include "src/ui/screens/notifications.h"
#include "src/managers/input_manager.h"
#include "src/managers/mood_manager.h"
#include "src/managers/emotion_manager.h"
#include "src/managers/display_manager.h"
#include "src/managers/weather_manager.h"
#include "src/managers/wifi_manager.h"
#include "src/managers/clock_manager.h"
#include "src/managers/sleep_manager.h"
#include "src/managers/demon_manager.h"
#include "src/managers/face_controller.h"
#include "src/managers/watchdog_manager.h"

#define TFT_CS   14
#define TFT_DC   15
#define TFT_RST  16

#define TFT_MOSI 17
#define TFT_SCLK 18

// --------------------------------------------------
// DISPLAY
// --------------------------------------------------

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);
U8G2_FOR_ADAFRUIT_GFX u8g2;

uint16_t KORE_CYAN;

// --------------------------------------------------
// DISPLAY STATES
// --------------------------------------------------

DisplayMode currentMode = DISPLAY_EMOTION;
bool modeChanged = false;

// --------------------------------------------------
// FACE TYPES
// --------------------------------------------------

FaceType currentFace = FACE_HAPPY;

// --------------------------------------------------
// BOOT STATE
// --------------------------------------------------

bool bootDone = false;

// --------------------------------------------------
// SETUP
// --------------------------------------------------

void setup()
{
    Serial.begin(115200);
    delay(1000);

    logResetReason();
    Serial.println("KORE_COMPANION");

    randomSeed(esp_random());

    loadEmotionRules();

    autoConnectWiFi();

    beginBLE();

    beginTCPServer();

    SPI.begin(
        TFT_SCLK,
        -1,
        TFT_MOSI,
        TFT_CS
    );

    tft.init(240, 320);
    tft.setRotation(1);

    KORE_CYAN =
        tft.color565(
            11,
            235,
            201
        );

    u8g2.begin(tft);
    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.setFontMode(1);
    u8g2.setForegroundColor(KORE_CYAN);

    initWatchdog();

    bootScreen(
        tft,
        KORE_CYAN
    );

    initBootAnimation();

    fcInit();
    fcRequest("boot", defaultFace, 10, 0);

    lastActivity = millis();
}

// --------------------------------------------------
// LOOP
// --------------------------------------------------

void loop()
{
    if (!bootDone)
    {
        bootDone = updateBootAnimation();
        if (!bootDone) return;
        modeChanged = true;
    }

    feedWatchdog();

    updateClock();
    updateSleepManager();
    updateWiFiManager();
    updateInputManager();
    updateDemonManager();
    fcUpdate();
    updateDisplayState();
    handleDisplayTransition();
    updateActiveModule();
    fcUpdate();
    renderCurrentDisplay();
}