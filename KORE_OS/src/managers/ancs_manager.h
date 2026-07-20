#ifndef ANCS_MANAGER_H
#define ANCS_MANAGER_H

#include <Arduino.h>
#include <NimBLEDevice.h>

static const NimBLEUUID ANCS_SERVICE_UUID("7905F431-B5CE-4E99-A40F-4B1E122D00D0");
static const NimBLEUUID ANCS_NS_UUID("9FBF120D-6301-42D9-8C58-25E699A21DBD");
static const NimBLEUUID ANCS_CP_UUID("69D1D8F3-45E1-49A8-9821-9BBDFDAAD9D9");
static const NimBLEUUID ANCS_DS_UUID("22EAC6E9-24D6-4BB5-BE44-B36ACE7C7BFB");

extern String ancsCommand;
extern bool ancsCommandPending;
extern bool ancsConnected;

void beginANCS();
void updateANCS();
void startANCS();
void stopANCS();

bool ancsIsConnected();
bool ancsAvailable();
String readANCSCommand();

#endif
