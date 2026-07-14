#ifndef ANCS_MANAGER_H
#define ANCS_MANAGER_H

#include <Arduino.h>
#include <NimBLEDevice.h>

// --------------------------------------------------
// GLOBALS
// --------------------------------------------------

String ancsCommand = "";
bool ancsCommandPending = false;
bool ancsConnected = false;

// --------------------------------------------------
// INITIALIZE ANCS
// --------------------------------------------------

void beginANCS()
{
    // TODO
    //
    // Initialize Apple Notification Center Service.
    //
    // This manager will act as a BLE Central (Client),
    // connect to an iPhone and translate ANCS events
    // into K.O.R.E. commands.
}

// --------------------------------------------------
// UPDATE ANCS
// --------------------------------------------------

void updateANCS()
{
    // TODO
    //
    // Poll ANCS events if necessary.
}

// --------------------------------------------------
// CONNECTION STATUS
// --------------------------------------------------

bool ancsIsConnected()
{
    return ancsConnected;
}

// --------------------------------------------------
// AVAILABLE
// --------------------------------------------------

bool ancsAvailable()
{
    return ancsCommandPending;
}

// --------------------------------------------------
// READ COMMAND
// --------------------------------------------------

String readANCSCommand()
{
    ancsCommandPending = false;

    String command =
        ancsCommand;

    ancsCommand = "";

    return command;
}

#endif