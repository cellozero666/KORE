#ifndef CLOCK_MANAGER_H
#define CLOCK_MANAGER_H

#include <Arduino.h>

struct ClockState
{
    uint8_t hour = 12;
    uint8_t minute = 0;
    uint8_t second = 0;
    unsigned long lastTick = 0;
};

extern ClockState clockState;

void updateClock();
void setClock(uint8_t hour, uint8_t minute, uint8_t second);

#endif
