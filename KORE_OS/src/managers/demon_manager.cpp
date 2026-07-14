#include <Arduino.h>
#include "demon_manager.h"
#include "face_controller.h"

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

const unsigned long DEMON_UPTIME =
    (66UL * 60UL * 60UL * 1000UL) +
    (6UL * 60UL * 1000UL);

bool demonTriggered = false;
static bool uptimeDemonTriggered = false;
static bool uptimeDemonActive = false;
static unsigned long uptimeDemonStart = 0;

bool isDemonTrack(String artist, String track)
{
    artist.toLowerCase();
    track.toLowerCase();

    for (size_t i = 0; i < sizeof(demonTracks) / sizeof(DemonTrack); i++)
    {
        String demonArtist = demonTracks[i].artist;
        String demonTrack = demonTracks[i].track;

        demonArtist.toLowerCase();
        demonTrack.toLowerCase();

        if (artist.indexOf(demonArtist) >= 0 && track.indexOf(demonTrack) >= 0)
        {
            return true;
        }
    }

    return false;
}

void updateDemonManager()
{
    if (uptimeDemonTriggered && !uptimeDemonActive)
        return;

    if (!uptimeDemonTriggered && millis() >= DEMON_UPTIME)
    {
        uptimeDemonTriggered = true;
        uptimeDemonActive = true;
        uptimeDemonStart = millis();
        fcRequest("uptime_demon", FACE_DEMON, 200, 5000);
        return;
    }

    if (uptimeDemonActive && millis() - uptimeDemonStart >= 5000)
    {
        uptimeDemonActive = false;
        fcRelease("uptime_demon");
    }
}
