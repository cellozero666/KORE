#ifndef TCP_MANAGER_H
#define TCP_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>

// --------------------------------------------------
// CONFIGURATION
// --------------------------------------------------

constexpr uint16_t KORE_TCP_PORT = 6666;

// --------------------------------------------------
// GLOBALS
// --------------------------------------------------

WiFiServer tcpServer(KORE_TCP_PORT);
WiFiClient tcpClient;

String tcpCommand = "";
bool tcpCommandPending = false;

// --------------------------------------------------
// INITIALIZE TCP SERVER
// --------------------------------------------------

void beginTCPServer()
{
    tcpServer.begin();
    tcpServer.setNoDelay(true);

    Serial.print("[TCP] Listening on port ");
    Serial.println(KORE_TCP_PORT);
}

// --------------------------------------------------
// UPDATE TCP SERVER
// --------------------------------------------------

void updateTCPServer()
{
    // Wait for client
    if (!tcpClient || !tcpClient.connected())
    {
        tcpClient = tcpServer.available();

        return;
    }

    // Read incoming command
    while (tcpClient.available())
    {
        tcpCommand =
            tcpClient.readStringUntil('\n');

        tcpCommand.trim();

        if (tcpCommand.length() > 0)
        {
            tcpCommandPending = true;

            Serial.print("[TCP RX] ");
            Serial.println(tcpCommand);
        }
    }
}

// --------------------------------------------------
// CONNECTION STATUS
// --------------------------------------------------

bool tcpIsConnected()
{
    return tcpClient.connected();
}

// --------------------------------------------------
// COMMAND AVAILABLE
// --------------------------------------------------

bool tcpCommandAvailable()
{
    return tcpCommandPending;
}

// --------------------------------------------------
// READ COMMAND
// --------------------------------------------------

String readTCPCommand()
{
    tcpCommandPending = false;

    String command =
        tcpCommand;

    tcpCommand = "";

    return command;
}

// --------------------------------------------------
// SEND COMMAND
// --------------------------------------------------

void sendTCPCommand(String command)
{
    if (!tcpClient.connected())
        return;

    tcpClient.println(command);
}

#endif