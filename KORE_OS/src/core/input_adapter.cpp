#include <Arduino.h>
#include "input_adapter.h"
#include "command_parser.h"
#include "../managers/ble_manager.h"
#include "../managers/ancs_manager.h"
#include "../managers/tcp_manager.h"

void updateInputAdapter()
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
