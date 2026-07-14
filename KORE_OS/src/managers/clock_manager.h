#ifndef CLOCK_MANAGER_H
#define CLOCK_MANAGER_H

#include <Arduino.h>

// --------------------------------------------------
// CLOCK
// --------------------------------------------------

struct ClockState
{
    uint8_t hour = 12;
    uint8_t minute = 0;
    uint8_t second = 0;

    unsigned long lastTick = 0;
};

ClockState clockState;

// --------------------------------------------------
// UPDATE
// --------------------------------------------------

void updateClock()
{
    if (millis() - clockState.lastTick < 1000)
        return;

    clockState.lastTick += 1000;

    clockState.second++;

    if (clockState.second >= 60)
    {
        clockState.second = 0;
        clockState.minute++;
    }

    if (clockState.minute >= 60)
    {
        clockState.minute = 0;
        clockState.hour++;
    }

    if (clockState.hour >= 24)
    {
        clockState.hour = 0;
    }

}

// --------------------------------------------------
// SET TIME
// --------------------------------------------------

void setClock(
    uint8_t hour,
    uint8_t minute,
    uint8_t second)
{
    clockState.hour = hour;
    clockState.minute = minute;
    clockState.second = second;

    clockState.lastTick = millis();
}

#endif