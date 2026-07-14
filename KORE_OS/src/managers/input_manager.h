#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <Arduino.h>

#include "../core/command_parser.h"
#include "ble_manager.h"
#include "ancs_manager.h"
#include "tcp_manager.h"

// --------------------------------------------------
// UPDATE INPUT MANAGER
// --------------------------------------------------

void updateInputManager() {
    // -----------------------------
    // SERIAL
    // -----------------------------
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        processCommand(command);
    }

    // -----------------------------
    // BLE
    // -----------------------------
    if (bleCommandAvailable()) {
        String command = readBLECommand();
        processCommand(command);
    }

    // -----------------------------
    // ANCS
    // -----------------------------
    if (ancsAvailable()) {
        String command = readANCSCommand();
        processCommand(command);
    }

    // -----------------------------
    // TCP
    // -----------------------------
    updateTCPServer();
    if (tcpCommandAvailable()) {
        String command = readTCPCommand();
        processCommand(command);
    }
}

#endif