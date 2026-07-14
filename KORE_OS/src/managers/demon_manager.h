#ifndef DEMON_MANAGER_H
#define DEMON_MANAGER_H

#include <Arduino.h>
#include "mood_manager.h"

struct DemonTrack
{
    const char *artist;
    const char *track;
};

extern const DemonTrack demonTracks[];
extern const unsigned long DEMON_UPTIME;

extern bool demonTriggered;

bool isDemonTrack(String artist, String track);
void updateDemonManager();

#endif
