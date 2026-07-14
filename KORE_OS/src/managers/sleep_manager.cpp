#include <Arduino.h>
#include "sleep_manager.h"
#include "clock_manager.h"
#include "mood_manager.h"
#include "display_manager.h"
#include "face_controller.h"

FaceType defaultFace = FACE_HAPPY;    // owned by sleep_manager — the only module that modifies it
unsigned long lastActivity = 0;        // owned by sleep_manager — used for idle detection

void updateSleepManager()
{
    FaceType newDefault = FACE_HAPPY;

    bool nightSleep =
        clockState.hour >= 22 ||
        clockState.hour < 7;

    bool idleSleep =
        !nightSleep &&
        (millis() - lastActivity >= IDLE_SLEEP_TIME);

    if (nightSleep)
    {
        newDefault = FACE_SLEEP;
    }
    else if (idleSleep)
    {
        newDefault = FACE_SLEEP;
    }

    if (newDefault == defaultFace)
        return;

    defaultFace = newDefault;

    if (currentMode == DISPLAY_EMOTION)
    {
        fcRequest("boot", defaultFace, 10, 0);
    }
}
