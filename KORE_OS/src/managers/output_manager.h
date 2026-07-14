#ifndef OUTPUT_MANAGER_H
#define OUTPUT_MANAGER_H

#include <Arduino.h>
#include "ble_manager.h"
#include "tcp_manager.h"

inline void sendResponse(const String& response) {
    Serial.println(response);

    if (bleIsConnected()) {
        sendBLECommand(response);
    }

    if (tcpIsConnected()) {
        sendTCPCommand(response);
    }
}

#endif
