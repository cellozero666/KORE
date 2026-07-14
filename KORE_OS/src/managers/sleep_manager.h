#ifndef SLEEP_MANAGER_H
#define SLEEP_MANAGER_H

#include <Arduino.h>

#define IDLE_SLEEP_TIME 900000UL

extern unsigned long lastActivity;

void updateSleepManager();

#endif
