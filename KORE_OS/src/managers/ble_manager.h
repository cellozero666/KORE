#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

#include <Arduino.h>
#include <NimBLEDevice.h>

constexpr char KORE_SERVICE_UUID[] = "8C0F0001-5A8F-4E7E-9D43-92D67E4D0001";
constexpr char KORE_RX_UUID[] = "8C0F0002-5A8F-4E7E-9D43-92D67E4D0001";
constexpr char KORE_TX_UUID[] = "8C0F0003-5A8F-4E7E-9D43-92D67E4D0001";

extern NimBLEServer * bleServer;
extern NimBLEService * bleService;
extern NimBLECharacteristic * bleRXCharacteristic;
extern NimBLECharacteristic * bleTXCharacteristic;
extern String bleCommand;
extern bool bleCommandPending;
extern bool bleConnected;
extern uint16_t ancsConnHandle;
extern bool ancsShouldConnect;

class KORE_ServerCallbacks: public NimBLEServerCallbacks {
  public:
    void onConnect(NimBLEServer*, NimBLEConnInfo&) override;
    void onDisconnect(NimBLEServer*, NimBLEConnInfo&, int) override;
    uint32_t onPassKeyDisplay() override;
    void onPassKeyEntry(NimBLEConnInfo& connInfo) override;
    void onConfirmPassKey(NimBLEConnInfo& connInfo, uint32_t pin) override;
    void onAuthenticationComplete(NimBLEConnInfo& connInfo) override;
};

class KORE_RX_Callbacks: public NimBLECharacteristicCallbacks {
  public:
    void onWrite(NimBLECharacteristic*, NimBLEConnInfo&) override;
};

void beginBLE();
bool bleIsConnected();
bool bleCommandAvailable();
String readBLECommand();
void sendBLECommand(String command);

#endif
