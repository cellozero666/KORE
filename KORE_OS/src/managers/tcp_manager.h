#ifndef TCP_MANAGER_H
#define TCP_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>

constexpr uint16_t KORE_TCP_PORT = 6666;

extern WiFiServer tcpServer;
extern WiFiClient tcpClient;
extern String tcpCommand;
extern bool tcpCommandPending;

void beginTCPServer();
void updateTCPServer();
bool tcpIsConnected();
bool tcpCommandAvailable();
String readTCPCommand();
void sendTCPCommand(String command);

#endif
