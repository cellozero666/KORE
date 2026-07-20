#include "ancs_manager.h"
#include "ble_manager.h"
#include <Arduino.h>

// --------------------------------------------------
// GLOBALS
// --------------------------------------------------

String ancsCommand = "";
bool ancsCommandPending = false;
bool ancsConnected = false;

static bool ancsInitialized = false;
static NimBLEClient* ancsClient = nullptr;
static NimBLERemoteService* ancsService = nullptr;
static NimBLERemoteCharacteristic* ancsNSChar = nullptr;
static NimBLERemoteCharacteristic* ancsCPChar = nullptr;
static NimBLERemoteCharacteristic* ancsDSChar = nullptr;

static bool ancsRequestPending = false;
static bool ancsCPWriteNeeded = false;
static uint32_t ancsPendingUID = 0;
static unsigned long ancsRequestTime = 0;
static uint8_t ancsDSBuffer[512];
static size_t ancsDSLength = 0;

// --------------------------------------------------
// FORWARD DECLARATIONS
// --------------------------------------------------

static void onNSNotify(
  NimBLERemoteCharacteristic* pChar,
  uint8_t* pData,
  size_t length,
  bool isNotify
);

static void onDSNotify(
  NimBLERemoteCharacteristic* pChar,
  uint8_t* pData,
  size_t length,
  bool isNotify
);

static void ancsParseDSBuffer();

// --------------------------------------------------
// NS CALLBACK
// --------------------------------------------------

static void onNSNotify(
  NimBLERemoteCharacteristic* pChar,
  uint8_t* pData,
  size_t length,
  bool isNotify
)
{
  Serial.printf("[ANCS] ⚡ NS notify received: %zu bytes, event=%d\n", length, length > 0 ? pData[0] : -1);

  if (length < 8)
  {
    Serial.println("[ANCS] NS packet too short, ignoring");
    return;
  }

  uint8_t eventId = pData[0];
  if (eventId != 0)
  {
    Serial.printf("[ANCS] NS event ignored (eventId=%d, only Added=0 processed)\n", eventId);
    return;
  }

  if (ancsRequestPending)
  {
    Serial.printf("[ANCS] CP write already pending for UID %u, queueing UID %u\n", ancsPendingUID, ancsPendingUID);
    return;
  }

  ancsPendingUID =
    (uint32_t)pData[4] |
    ((uint32_t)pData[5] << 8) |
    ((uint32_t)pData[6] << 16) |
    ((uint32_t)pData[7] << 24);

  Serial.printf("[ANCS] New notification — UID: %u (deferred CP write)\n", ancsPendingUID);
  ancsRequestPending = true;
  ancsCPWriteNeeded = true;
  ancsRequestTime = millis();
}

// --------------------------------------------------
// DS CALLBACK
// --------------------------------------------------

static void onDSNotify(
  NimBLERemoteCharacteristic* pChar,
  uint8_t* pData,
  size_t length,
  bool isNotify
)
{
  Serial.printf("[ANCS] ⚡ DS notify received: %zu bytes", length);
  Serial.print("  raw:");
  for (size_t i = 0; i < length && i < 64; i++) {
    Serial.printf(" %02x", pData[i]);
  }
  if (length > 64) Serial.print(" ...");
  Serial.println();

  if (length == 0 || length > sizeof(ancsDSBuffer))
  {
    Serial.println("[ANCS] DS packet too large or empty, ignoring");
    return;
  }

  memcpy(ancsDSBuffer, pData, length);
  ancsDSLength = length;
}

// --------------------------------------------------
// ATTRIBUTE PARSING
// --------------------------------------------------

static void ancsParseDSBuffer()
{
  if (ancsDSLength < 5)
  {
    Serial.printf("[ANCS] DS buffer too short for parsing (%zu bytes), discarding\n", ancsDSLength);
    ancsDSLength = 0;
    ancsRequestPending = false;
    return;
  }

  uint8_t cmdId = ancsDSBuffer[0];
  Serial.printf("[ANCS] Parsing DS buffer: %zu bytes, cmdId=0x%02x\n", ancsDSLength, cmdId);

  if (cmdId != 0x00)
  {
    Serial.printf("[ANCS] Unknown DS command ID 0x%02x, discarding\n", cmdId);
    ancsDSLength = 0;
    ancsRequestPending = false;
    return;
  }

  String appId;
  String title;
  String message;

  size_t offset = 5;
  while (offset + 3 <= ancsDSLength)
  {
    uint8_t attrId = ancsDSBuffer[offset];
    uint16_t attrLen =
      (uint16_t)ancsDSBuffer[offset + 1] |
      ((uint16_t)ancsDSBuffer[offset + 2] << 8);
    offset += 3;

    if (offset + attrLen > ancsDSLength)
    {
      Serial.printf("[ANCS] Truncated attribute %d at offset %zu\n", attrId, offset);
      break;
    }

    String attrValue;
    attrValue.reserve(attrLen + 1);
    for (uint16_t i = 0; i < attrLen; i++)
    {
      attrValue += (char)ancsDSBuffer[offset + i];
    }
    offset += attrLen;

    Serial.printf("[ANCS] Attribute id=%d, len=%u, value=\"%s\"\n", attrId, attrLen, attrValue.c_str());

    switch (attrId)
    {
      case 0x00: appId = attrValue; break;
      case 0x01: title = attrValue; break;
      case 0x03: message = attrValue; break;
    }
  }

  ancsDSLength = 0;
  ancsRequestPending = false;

  if (appId.isEmpty())
  {
    Serial.println("[ANCS] No AppIdentifier received, discarding notification");
    return;
  }

  String command = "notification|";
  command += appId;
  command += "|";
  command += title;
  command += "|";
  command += message;

  Serial.printf("[ANCS] → Input Adapter: %s\n", command.c_str());
  ancsCommand = command;
  ancsCommandPending = true;
}

// --------------------------------------------------
// DISCOVER ANCS SERVICE
// --------------------------------------------------

static bool ancsDiscoverService()
{
  Serial.println("[ANCS] Step 1/4: Discovering ANCS service...");

  ancsService = ancsClient->getService(ANCS_SERVICE_UUID);
  if (ancsService == nullptr)
  {
    Serial.println("[ANCS] ✗ ANCS SERVICE NOT FOUND — iPhone does not expose ANCS on this connection");
    return false;
  }
  Serial.printf("[ANCS] ✓ ANCS service found (handle range: %d–%d)\n",
    ancsService->getStartHandle(), ancsService->getEndHandle());

  Serial.println("[ANCS] === DIAGNOSTIC: discovering ALL characteristics ===");
  const auto& allChars = ancsService->getCharacteristics(true);
  Serial.printf("[ANCS] Total characteristics discovered: %zu\n", allChars.size());

  ancsNSChar = nullptr;
  ancsCPChar = nullptr;
  ancsDSChar = nullptr;

  for (auto& c : allChars) {
    NimBLEUUID cuuid = c->getUUID();
    Serial.printf("[ANCS]   handle=%d uuid=%s canRead=%d canWrite=%d canWriteNoRsp=%d canNotify=%d\n",
      c->getHandle(),
      cuuid.toString().c_str(),
      c->canRead() ? 1 : 0,
      c->canWrite() ? 1 : 0,
      c->canWriteNoResponse() ? 1 : 0,
      c->canNotify() ? 1 : 0);

    if (cuuid == ANCS_NS_UUID) {
      ancsNSChar = c;
      Serial.printf("[ANCS]   → mapped as NS\n");
    } else if (cuuid == ANCS_DS_UUID) {
      ancsDSChar = c;
      Serial.printf("[ANCS]   → mapped as DS\n");
    } else if (cuuid == ANCS_CP_UUID) {
      ancsCPChar = c;
      Serial.printf("[ANCS]   → mapped as CP (standard UUID)\n");
    } else if (!ancsCPChar && (c->canWrite() || c->canWriteNoResponse())) {
      // Not NS, not DS, but supports Write — use as CP fallback only if not already set
      ancsCPChar = c;
      Serial.printf("[ANCS]   → mapped as CP (fallback — unknown writable char)\n");
    } else {
      Serial.printf("[ANCS]   (unexpected char, ignoring)\n");
    }
  }
  Serial.println("[ANCS] === END DIAGNOSTIC ===");

  if (ancsNSChar == nullptr) {
    Serial.println("[ANCS] ✗ Notification Source NOT FOUND");
    return false;
  }
  if (ancsDSChar == nullptr) {
    Serial.println("[ANCS] ✗ Data Source NOT FOUND");
    return false;
  }
  if (ancsCPChar == nullptr) {
    Serial.println("[ANCS] ✗ Control Point NOT FOUND — no writable characteristic available");
    return false;
  }

  Serial.printf("[ANCS] ✓ NS@%d CP@%d DS@%d — ready\n",
    ancsNSChar->getHandle(),
    ancsCPChar->getHandle(),
    ancsDSChar->getHandle());
  return true;
}

// --------------------------------------------------
// SUBSCRIBE TO NOTIFICATIONS
// --------------------------------------------------

static bool ancsSubscribe()
{
  if (ancsNSChar == nullptr)
  {
    Serial.println("[ANCS] Cannot subscribe — NS char is null");
    return false;
  }
  if (ancsDSChar == nullptr)
  {
    Serial.println("[ANCS] Cannot subscribe — DS char is null");
    return false;
  }

  Serial.println("[ANCS] Subscribing to Notification Source notifications...");
  bool nsOk = ancsNSChar->subscribe(true, onNSNotify, true);
  Serial.printf("[ANCS] NS subscribe: %s\n", nsOk ? "OK" : "FAILED");
  if (!nsOk) return false;

  Serial.println("[ANCS] Subscribing to Data Source notifications...");
  bool dsOk = ancsDSChar->subscribe(true, onDSNotify, true);
  Serial.printf("[ANCS] DS subscribe: %s\n", dsOk ? "OK" : "FAILED");
  if (!dsOk) return false;

  Serial.println("[ANCS] ✓ Both subscriptions registered — ready for notifications");
  return true;
}

// --------------------------------------------------
// PUBLIC API
// --------------------------------------------------

void beginANCS()
{
  ancsInitialized = true;
  ancsConnected = false;
  ancsDSLength = 0;
  ancsRequestPending = false;
  ancsService = nullptr;
  ancsNSChar = nullptr;
  ancsCPChar = nullptr;
  ancsDSChar = nullptr;
  ancsClient = nullptr;
  Serial.println("[ANCS] Manager initialized (shared connection mode)");
}

void startANCS()
{
  if (!ancsInitialized)
  {
    Serial.println("[ANCS] Cannot start — not initialized");
    return;
  }

  if (ancsConnected)
  {
    Serial.println("[ANCS] Already connected, skipping");
    return;
  }

  if (ancsConnHandle == BLE_HS_CONN_HANDLE_NONE)
  {
    Serial.println("[ANCS] No valid connection handle available");
    return;
  }

  Serial.print("[ANCS] Getting client for connection handle ");
  Serial.println(ancsConnHandle);

  ancsClient = bleServer->getClient(ancsConnHandle);
  if (ancsClient == nullptr)
  {
    Serial.println("[ANCS] ✗ getClient() returned null — connection may be gone");
    ancsConnHandle = BLE_HS_CONN_HANDLE_NONE;
    return;
  }

  Serial.printf("[ANCS] Client obtained — peer: %s, handle: %d, connected: %d\n",
    ancsClient->getPeerAddress().toString().c_str(),
    ancsClient->getConnHandle(),
    ancsClient->isConnected() ? 1 : 0);

  if (!ancsDiscoverService())
  {
    Serial.println("[ANCS] ✗ ANCS service discovery failed");
    ancsClient = nullptr;
    return;
  }

  if (!ancsSubscribe())
  {
    Serial.println("[ANCS] ✗ Subscription failed");
    ancsClient = nullptr;
    return;
  }

  ancsConnected = true;
  Serial.println("[ANCS] ✅ SETUP COMPLETE — listening for iPhone notifications via shared connection");
}

void stopANCS()
{
  ancsConnected = false;
  ancsClient = nullptr;
  ancsService = nullptr;
  ancsNSChar = nullptr;
  ancsCPChar = nullptr;
  ancsDSChar = nullptr;
  ancsDSLength = 0;
  ancsRequestPending = false;
  ancsCPWriteNeeded = false;
  ancsCommandPending = false;
  ancsCommand = "";

  Serial.println("[ANCS] Stopped — ANCS client references cleared");
}

static void ancsSendCPWrite()
{
  if (ancsCPChar == nullptr)
  {
    Serial.println("[ANCS] CP char not available, cannot send CP write");
    ancsRequestPending = false;
    return;
  }

  uint8_t cmd[12];
  memset(cmd, 0, sizeof(cmd));
  cmd[0] = 0x00;
  cmd[1] = ancsPendingUID & 0xFF;
  cmd[2] = (ancsPendingUID >> 8) & 0xFF;
  cmd[3] = (ancsPendingUID >> 16) & 0xFF;
  cmd[4] = (ancsPendingUID >> 24) & 0xFF;
  cmd[5] = 0x00;
  cmd[6] = 0x01;
  cmd[7] = 64;
  cmd[8] = 0x00;
  cmd[9] = 0x03;
  cmd[10] = 256;
  cmd[11] = 0x01;

  Serial.printf("[ANCS] CP write (AppID+Title+Msg) for UID %u ...\n", ancsPendingUID);

  uint16_t connHandle = ancsCPChar->getClient()->getConnHandle();
  uint16_t charHandle = ancsCPChar->getHandle();
  Serial.printf("[ANCS]   connHandle=%u charHandle=%u uuid=%s\n",
    connHandle, charHandle, ancsCPChar->getUUID().toString().c_str());
  Serial.printf("[ANCS]   cmd (%zu bytes):", sizeof(cmd));
  for (size_t i = 0; i < sizeof(cmd); i++) {
    Serial.printf(" %02x", cmd[i]);
  }
  Serial.println();

  bool ok = ancsCPChar->writeValue(cmd, sizeof(cmd), true);

  if (ok)
  {
    Serial.printf("[ANCS] CP write OK for UID %u\n", ancsPendingUID);
  }
  else
  {
    Serial.printf("[ANCS] CP write FAILED for UID %u\n", ancsPendingUID);
    ancsRequestPending = false;
  }
}

void updateANCS()
{
  if (ancsRequestPending)
  {
    if (ancsCPWriteNeeded)
    {
      ancsCPWriteNeeded = false;
      ancsSendCPWrite();
    }

    if (millis() - ancsRequestTime > 5000)
    {
      Serial.printf("[ANCS] ⏱ DS response timeout for UID %u — clearing\n", ancsPendingUID);
      ancsRequestPending = false;
    }
  }

  if (ancsDSLength > 0)
  {
    ancsParseDSBuffer();
  }

  if (!ancsShouldConnect) return;
  if (ancsConnected) return;
  if (ancsConnHandle == BLE_HS_CONN_HANDLE_NONE) return;

  ancsShouldConnect = false;
  startANCS();
}

bool ancsIsConnected()
{
  return ancsConnected;
}

bool ancsAvailable()
{
  return ancsCommandPending;
}

String readANCSCommand()
{
  ancsCommandPending = false;
  String command = ancsCommand;
  ancsCommand = "";
  return command;
}
