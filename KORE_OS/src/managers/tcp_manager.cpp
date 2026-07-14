#include <Arduino.h>
#include <WiFi.h>
#include "tcp_manager.h"

WiFiServer tcpServer(KORE_TCP_PORT);
WiFiClient tcpClient;
String tcpCommand = "";
bool tcpCommandPending = false;

void beginTCPServer()
{
    tcpServer.begin();
    tcpServer.setNoDelay(true);
    Serial.print("[TCP] Listening on port ");
    Serial.println(KORE_TCP_PORT);
}

void updateTCPServer()
{
    if (!tcpClient || !tcpClient.connected())
    {
        tcpClient = tcpServer.available();
        return;
    }

    while (tcpClient.available())
    {
        tcpCommand = tcpClient.readStringUntil('\n');
        tcpCommand.trim();

        if (tcpCommand.length() > 0)
        {
            tcpCommandPending = true;
            Serial.print("[TCP RX] ");
            Serial.println(tcpCommand);
        }
    }
}

bool tcpIsConnected()
{
    return tcpClient.connected();
}

bool tcpCommandAvailable()
{
    return tcpCommandPending;
}

String readTCPCommand()
{
    tcpCommandPending = false;
    String command = tcpCommand;
    tcpCommand = "";
    return command;
}

void sendTCPCommand(String command)
{
    if (!tcpClient.connected())
        return;
    tcpClient.println(command);
}
