#ifndef DEMON_MANAGER_H
#define DEMON_MANAGER_H

#include <Arduino.h>
#include "mood_manager.h"

// --------------------------------------------------
// TRACK LIST
// --------------------------------------------------

struct DemonTrack
{
    const char *artist;
    const char *track;
};

const DemonTrack demonTracks[] =
{
    {"ghost", "year zero"},
    {"black sabbath", "sabbath bloody sabbath"},
    {"slayer", "angel of death"},
    {"celtic frost", "procreation (of the wicked)"},
    {"sepultura", "procreation (of the wicked)"},
    {"venom", "countess bathory"},
    {"iron maiden", "the number of the beast"},
    {"uncle acid & the deadbeats", "blood runner"},
    {"brujeria", "brujerizmo"},
    {"type o negative", "red water"},
    {"mercyful fate", "come to the sabbath"},
    {"dethklok", "castratikron"}, 
};

// --------------------------------------------------
// FLAGS
// --------------------------------------------------

static bool demonTriggered = false;

static bool uptimeDemonTriggered = false;
static bool uptimeDemonActive = false;

static unsigned long uptimeDemonStart = 0;

static FaceType uptimePreviousFace;

// 66h06m

const unsigned long DEMON_UPTIME =
    (66UL * 60UL * 60UL * 1000UL) +
    (6UL * 60UL * 1000UL);

// --------------------------------------------------
// SPOTIFY TRACK MATCH
// --------------------------------------------------

bool isDemonTrack(
    String artist,
    String track
)
{
    artist.toLowerCase();
    track.toLowerCase();

    for (size_t i = 0; i < sizeof(demonTracks) / sizeof(DemonTrack); i++)
    {
        String demonArtist = demonTracks[i].artist;
        String demonTrack = demonTracks[i].track;

        demonArtist.toLowerCase();
        demonTrack.toLowerCase();

        if (
            artist.indexOf(demonArtist) >= 0 &&
            track.indexOf(demonTrack) >= 0
        )
        {
            return true;
        }
    }

    return false;
}

// --------------------------------------------------
// UPTIME DEMON
// --------------------------------------------------

void updateDemonManager()
{
    // já terminou tudo
    if (uptimeDemonTriggered && !uptimeDemonActive)
        return;

    // dispara aos 66h06m
    if (
        !uptimeDemonTriggered &&
        millis() >= DEMON_UPTIME
    )
    {
        uptimeDemonTriggered = true;
        uptimeDemonActive = true;

        uptimePreviousFace = currentFace;

        uptimeDemonStart = millis();

        setFace(FACE_DEMON);

        return;
    }

    // encerra após 5 segundos
    if (
        uptimeDemonActive &&
        millis() - uptimeDemonStart >= 5000
    )
    {
        uptimeDemonActive = false;

        setFace(uptimePreviousFace);
    }
}

#endif