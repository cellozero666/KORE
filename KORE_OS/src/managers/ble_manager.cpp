#include <Arduino.h>
#include <NimBLEDevice.h>
#include "ble_manager.h"

NimBLEServer * bleServer = nullptr;
NimBLEService * bleService = nullptr;
NimBLECharacteristic * bleRXCharacteristic = nullptr;
NimBLECharacteristic * bleTXCharacteristic = nullptr;
String bleCommand = "";
bool bleCommandPending = false;
bool bleConnected = false;

void KORE_ServerCallbacks::onConnect(
    NimBLEServer *,
    NimBLEConnInfo &
) {
    bleConnected = true;
    Serial.println("[BLE] Device Connected");
}

void KORE_ServerCallbacks::onDisconnect(
    NimBLEServer * server,
    NimBLEConnInfo &,
    int
) {
    bleConnected = false;
    Serial.println("[BLE] Device Disconnected");
    bool ok = server->startAdvertising();
    Serial.print("[BLE] Restart Advertising: ");
    Serial.println(ok ? "OK" : "FAILED");
}

void KORE_RX_Callbacks::onWrite(
    NimBLECharacteristic * characteristic,
    NimBLEConnInfo &
) {
    std::string value = characteristic->getValue();
    bleCommand = String(value.c_str());
    bleCommand.trim();
    if (bleCommand.length() > 0)
    {
        bleCommandPending = true;
        Serial.print("[BLE RX] ");
        Serial.println(bleCommand);
    }
}

void beginBLE()
{
    NimBLEDevice::init("K.O.R.E.");
    bleServer = NimBLEDevice::createServer();
    bleServer->setCallbacks(new KORE_ServerCallbacks());
    bleService = bleServer->createService(KORE_SERVICE_UUID);
    bleRXCharacteristic = bleService->createCharacteristic(
        KORE_RX_UUID,
        NIMBLE_PROPERTY::WRITE
    );
    bleTXCharacteristic = bleService->createCharacteristic(
        KORE_TX_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    bleRXCharacteristic->setCallbacks(new KORE_RX_Callbacks());
    bleService->start();

    NimBLEAdvertising * advertising = NimBLEDevice::getAdvertising();
    advertising->setName("K.O.R.E.");
    advertising->addServiceUUID(KORE_SERVICE_UUID);
    advertising->enableScanResponse(true);

    bool ok = advertising->start();
    Serial.print("[BLE] Advertising: ");
    Serial.println(ok ? "OK" : "FAILED");
}

bool bleIsConnected()
{
    return bleConnected;
}

bool bleCommandAvailable()
{
    return bleCommandPending;
}

String readBLECommand()
{
    bleCommandPending = false;
    String command = bleCommand;
    bleCommand = "";
    return command;
}

void sendBLECommand(String command)
{
    if (!bleConnected)
        return;
    bleTXCharacteristic->setValue(command.c_str());
    bleTXCharacteristic->notify();
}
