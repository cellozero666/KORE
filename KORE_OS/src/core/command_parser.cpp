#include <Arduino.h>
#include "command_parser.h"
#include "../config/config.h"
#include "../managers/output_manager.h"
#include "../managers/mood_manager.h"
#include "../managers/clock_manager.h"
#include "../managers/face_controller.h"
#include "../ui/screens/notifications.h"
#include "../ui/screens/spotify_screen.h"
#include "../managers/wifi_manager.h"
#include "../managers/weather_manager.h"

void processCommand(String command)
{
    command.trim();
    lastActivity = millis();

    if (command == "ping")
    {
        sendResponse("KORE_COMPANION");
    }
    else if (command.startsWith("notification|"))
    {
        parseNotificationCommand(command);
        notificationWasDrawn = false;
    }
    else if (command.startsWith("weather|"))
    {
        handleWeatherCommand(command);
    }
    else if (command.startsWith("spotify|"))
    {
        if (!spotifyActive)
        {
            spotifyFaceTimer = millis();
        }
        parseSpotifyCommand(command);
    }
    else if (command == "spotify_stop")
    {
        spotifyActive = false;
        fcRelease("spotify_demon");
    }
    else if (command == "version")
    {
        sendResponse("version|" + String(FIRMWARE_VERSION));
    }
    else if (command == "current_face")
    {
        sendResponse("current_face|" + getCurrentFaceName());
    }
    else if (command == "uptime")
    {
        sendResponse("uptime|" + String(millis() / 1000));
    }
    else if (command == "wifi_status")
    {
        sendResponse("wifi_status|" + getWiFiStatus());
    }
    else if (command.startsWith("wifi_connect|"))
    {
        int separator = command.indexOf('|');
        if (separator < 0) return;

        String data = command.substring(separator + 1);
        int separator2 = data.indexOf('|');
        if (separator2 < 0) return;

        String ssid = data.substring(0, separator2);
        String password = data.substring(separator2 + 1);
        connectWiFi(ssid, password);
        sendResponse("wifi_connect|WIFI_CONNECTING");
    }
    else if (command.startsWith("time|"))
    {
        int p1 = command.indexOf('|');
        int p2 = command.indexOf('|', p1 + 1);
        int p3 = command.indexOf('|', p2 + 1);
        if (p1 < 0 || p2 < 0 || p3 < 0) return;

        uint8_t hour = command.substring(p1 + 1, p2).toInt();
        uint8_t minute = command.substring(p2 + 1, p3).toInt();
        uint8_t second = command.substring(p3 + 1).toInt();
        setClock(hour, minute, second);

        char buffer[64];
        snprintf(buffer, sizeof(buffer), "time|Clock synchronized %02d:%02d:%02d", hour, minute, second);
        sendResponse(buffer);
    }
    else
    {
        if (command == "happy")       { fcRequest("default", FACE_HAPPY, 10, 0); }
        else if (command == "extrahappy") { fcRequest("default", FACE_EXTRA_HAPPY, 10, 0); }
        else if (command == "sad")    { fcRequest("default", FACE_SAD, 10, 0); }
        else if (command == "sleep")  { fcRequest("default", FACE_SLEEP, 10, 0); }
        else if (command == "surprise") { fcRequest("default", FACE_SURPRISE, 10, 0); }
        else if (command == "loving") { fcRequest("default", FACE_LOVING, 10, 0); }
        else if (command == "confused") { fcRequest("default", FACE_CONFUSED, 10, 0); }
        else if (command == "demon")  { fcRequest("default", FACE_DEMON, 10, 0); }
    }
}
