#include <Arduino.h>
#include "clock_manager.h"

ClockState clockState;

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

void setClock(uint8_t hour, uint8_t minute, uint8_t second)
{
    clockState.hour = hour;
    clockState.minute = minute;
    clockState.second = second;
    clockState.lastTick = millis();
}
