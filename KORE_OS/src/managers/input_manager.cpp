#include <Arduino.h>
#include "input_manager.h"
#include "../core/command_parser.h"
#include "ble_manager.h"
#include "ancs_manager.h"
#include "tcp_manager.h"

void updateInputManager()
{
    if (Serial.available())
    {
        String command = Serial.readStringUntil('\n');
        processCommand(command);
    }

    if (bleCommandAvailable())
    {
        String command = readBLECommand();
        processCommand(command);
    }

    if (ancsAvailable())
    {
        String command = readANCSCommand();
        processCommand(command);
    }

    updateTCPServer();
    if (tcpCommandAvailable())
    {
        String command = readTCPCommand();
        processCommand(command);
    }
}
