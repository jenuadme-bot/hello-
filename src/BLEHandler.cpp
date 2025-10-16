/*#include "BLEHandler.h"

bool BLEHandler::deviceConnected = false;
String BLEHandler::validToken = "";

// ===============================
// Custom server callback class
// ===============================
class MyServerCallbacks : public NimBLEServerCallbacks {
  void onConnect(NimBLEServer* pServer) {
    BLEHandler::deviceConnected = true;
    Serial.println("Device connected");
  }

  void onDisconnect(NimBLEServer* pServer) {
    BLEHandler::deviceConnected = false;
    Serial.println("Device disconnected — restarting advertising");
    NimBLEDevice::startAdvertising();
  }
};

// ===============================
// Custom characteristic callback
// ===============================
class MyCharacteristicCallbacks : public NimBLECharacteristicCallbacks {
  void onWrite(NimBLECharacteristic* c) {
    std::string value = c->getValue();
    Serial.print("Received: ");
    Serial.println(value.c_str());

    if (value == BLEHandler::validToken.c_str()) {
      c->setValue("AUTH OK");
      Serial.println("Authentication success");
    } else {
      c->setValue("INVALID TOKEN");
      Serial.println("Authentication failed");
    }
  }
};

// ===============================
// BLEHandler implementation
// ===============================
BLEHandler::BLEHandler() {}

void BLEHandler::begin() {
  NimBLEDevice::init("BondBand_01");
  NimBLEServer* server = NimBLEDevice::createServer();

  // Attach callbacks
  server->setCallbacks(new MyServerCallbacks());

  // Create service and characteristic
  NimBLEService* service = server->createService("1234");
  NimBLECharacteristic* characteristic = service->createCharacteristic(
      "abcd",
      NIMBLE_PROPERTY::READ |
      NIMBLE_PROPERTY::WRITE |
      NIMBLE_PROPERTY::NOTIFY
  );

  characteristic->setValue("Awaiting token...");
  characteristic->setCallbacks(new MyCharacteristicCallbacks());

  service->start();

  NimBLEAdvertising* adv = NimBLEDevice::getAdvertising();
  adv->addServiceUUID("1234");
  adv->start();

  Serial.println("BLE started and advertising...");
}

void BLEHandler::loop() {
  if (!deviceConnected) {
    NimBLEDevice::startAdvertising();
  }
}

bool BLEHandler::isConnected() {
  return deviceConnected;
}

void BLEHandler::setAuthToken(String token) {
  validToken = token;
}*/
