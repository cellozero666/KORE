#include <Arduino.h>
#include <NimBLEDevice.h>
#include "ble_manager.h"
#include "ancs_manager.h"

NimBLEServer * bleServer = nullptr;
NimBLEService * bleService = nullptr;
NimBLECharacteristic * bleRXCharacteristic = nullptr;
NimBLECharacteristic * bleTXCharacteristic = nullptr;
String bleCommand = "";
bool bleCommandPending = false;
bool bleConnected = false;
uint16_t ancsConnHandle = BLE_HS_CONN_HANDLE_NONE;
bool ancsShouldConnect = false;

void KORE_ServerCallbacks::onConnect(
    NimBLEServer *,
    NimBLEConnInfo & connInfo
) {
    bleConnected = true;
    ancsConnHandle = connInfo.getConnHandle();
    Serial.print("[BLE] Device Connected — handle: ");
    Serial.print(ancsConnHandle);
    Serial.print(", ID: ");
    Serial.println(connInfo.getIdAddress().toString().c_str());
}

void KORE_ServerCallbacks::onDisconnect(
    NimBLEServer * server,
    NimBLEConnInfo &,
    int
) {
    bleConnected = false;
    ancsConnHandle = BLE_HS_CONN_HANDLE_NONE;
    ancsShouldConnect = false;
    stopANCS();
    Serial.println("[BLE] Device Disconnected");
    bool ok = server->startAdvertising();
    Serial.print("[BLE] Restart Advertising: ");
    Serial.println(ok ? "OK" : "FAILED");
}

// --------------------------------------------------
// SECURITY CALLBACKS (integrated in NimBLEServerCallbacks)
// --------------------------------------------------

uint32_t KORE_ServerCallbacks::onPassKeyDisplay()
{
    Serial.println("[BLE SEC] Passkey display request (Just Works — returning 0)");
    return 0;
}

void KORE_ServerCallbacks::onPassKeyEntry(NimBLEConnInfo &)
{
    Serial.println("[BLE SEC] Passkey entry requested — not supported (Just Works)");
}

void KORE_ServerCallbacks::onConfirmPassKey(NimBLEConnInfo & connInfo, uint32_t pin)
{
    Serial.printf("[BLE SEC] Confirm passkey: %06u — auto-accepting\n", pin);
}

void KORE_ServerCallbacks::onAuthenticationComplete(NimBLEConnInfo & connInfo)
{
    if (connInfo.isEncrypted())
    {
        Serial.println("[BLE SEC] ✅ Authentication complete — encrypted channel established");
        ancsShouldConnect = true;
    }
    else
    {
        Serial.println("[BLE SEC] ❌ Authentication failed or incomplete");
    }
}

// --------------------------------------------------
// RX CALLBACKS
// --------------------------------------------------

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

// --------------------------------------------------
// INIT
// --------------------------------------------------

void beginBLE()
{
    NimBLEDevice::init("K.O.R.E.");

    // Configure BLE security: bonding, MITM, secure connections
    NimBLEDevice::setSecurityAuth(true, true, true);
    NimBLEDevice::setSecurityIOCap(BLE_HS_IO_NO_INPUT_OUTPUT);

    bleServer = NimBLEDevice::createServer();
    bleServer->setCallbacks(new KORE_ServerCallbacks());
    bleService = bleServer->createService(KORE_SERVICE_UUID);

    // RX characteristic — requires encryption for write (protected operation)
    bleRXCharacteristic = bleService->createCharacteristic(
        KORE_RX_UUID,
        NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_ENC
    );

    // TX characteristic — requires encryption for read
    bleTXCharacteristic = bleService->createCharacteristic(
        KORE_TX_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::READ_ENC | NIMBLE_PROPERTY::NOTIFY
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
