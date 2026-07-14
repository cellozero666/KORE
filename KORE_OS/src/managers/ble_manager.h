#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

#include <Arduino.h>
#include <NimBLEDevice.h>

// --------------------------------------------------
// K.O.R.E. BLE UUIDs
// --------------------------------------------------

constexpr char KORE_SERVICE_UUID[] = "8C0F0001-5A8F-4E7E-9D43-92D67E4D0001";
constexpr char KORE_RX_UUID[] = "8C0F0002-5A8F-4E7E-9D43-92D67E4D0001";
constexpr char KORE_TX_UUID[] = "8C0F0003-5A8F-4E7E-9D43-92D67E4D0001";

// --------------------------------------------------
// GLOBALS
// --------------------------------------------------

NimBLEServer * bleServer = nullptr;
NimBLEService * bleService = nullptr;

NimBLECharacteristic * bleRXCharacteristic = nullptr;
NimBLECharacteristic * bleTXCharacteristic = nullptr;

String bleCommand = "";
bool bleCommandPending = false;
bool bleConnected = false;

// --------------------------------------------------
// SERVER CALLBACKS
// --------------------------------------------------

class KORE_ServerCallbacks: public NimBLEServerCallbacks {

  public:

    void onConnect(
      NimBLEServer * ,
      NimBLEConnInfo &
    ) override {
      bleConnected = true;

      Serial.println("[BLE] Device Connected");
    }

  void onDisconnect(
    NimBLEServer * server,
    NimBLEConnInfo & ,
    int
  ) override {
    bleConnected = false;

    Serial.println("[BLE] Device Disconnected");

    bool ok = server -> startAdvertising();

    Serial.print("[BLE] Restart Advertising: ");
    Serial.println(ok ? "OK" : "FAILED");
  }
};

// --------------------------------------------------
// RX CALLBACK
// --------------------------------------------------

class KORE_RX_Callbacks: public NimBLECharacteristicCallbacks {

  public:

    void onWrite(
      NimBLECharacteristic * characteristic,
      NimBLEConnInfo &
    ) override {
      std::string value =
        characteristic -> getValue();

      bleCommand =
        String(value.c_str());

      bleCommand.trim();

      if (bleCommand.length() > 0) {
        bleCommandPending = true;

        Serial.print("[BLE RX] ");
        Serial.println(bleCommand);
      }
    }
};

// --------------------------------------------------
// INITIALIZE BLE
// --------------------------------------------------

void beginBLE() {
  NimBLEDevice::init("K.O.R.E.");

  bleServer =
    NimBLEDevice::createServer();

  bleServer -> setCallbacks(
    new KORE_ServerCallbacks()
  );

  bleService =
    bleServer -> createService(
      KORE_SERVICE_UUID
    );

  bleRXCharacteristic =
    bleService -> createCharacteristic(
      KORE_RX_UUID,
      NIMBLE_PROPERTY::WRITE
    );

  bleTXCharacteristic =
    bleService -> createCharacteristic(
      KORE_TX_UUID,
      NIMBLE_PROPERTY::READ |
      NIMBLE_PROPERTY::NOTIFY
    );

  bleRXCharacteristic -> setCallbacks(
    new KORE_RX_Callbacks()
  );

  bleService -> start();

  NimBLEAdvertising * advertising =
    NimBLEDevice::getAdvertising();

  advertising -> setName(
    "K.O.R.E."
  );

  advertising -> addServiceUUID(
    KORE_SERVICE_UUID
  );

  advertising -> enableScanResponse(true);

  bool ok =
    advertising -> start();

  Serial.print("[BLE] Advertising: ");
  Serial.println(ok ? "OK" : "FAILED");
}

// --------------------------------------------------
// CONNECTION STATUS
// --------------------------------------------------

bool bleIsConnected() {
  return bleConnected;
}

// --------------------------------------------------
// AVAILABLE
// --------------------------------------------------

bool bleCommandAvailable() {
  return bleCommandPending;
}

// --------------------------------------------------
// READ COMMAND
// --------------------------------------------------

String readBLECommand() {
  bleCommandPending = false;

  String command =
    bleCommand;

  bleCommand = "";

  return command;
}

// --------------------------------------------------
// SEND COMMAND
// --------------------------------------------------

void sendBLECommand(String command) {
  if (!bleConnected)
    return;

  bleTXCharacteristic -> setValue(
    command.c_str()
  );

  bleTXCharacteristic -> notify();
}

#endif