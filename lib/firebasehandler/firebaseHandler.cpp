#include <Arduino.h>
#include <NimBLEDevice.h>

#define LED_PIN 2

#define SERVICE_UUID        "55555555-aaaa-bbbb-cccc-111111111111"
#define CHARACTERISTIC_UUID "66666666-aaaa-bbbb-cccc-111111111111"

class RXCallbacks : public NimBLECharacteristicCallbacks {
  void onWrite(NimBLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    Serial.println("onWrite fired");
    if (value.length() > 0) {
      Serial.print("Received: ");
      Serial.println(value.c_str());
      if (value == "AUTH_12345") {
        Serial.println("✅ Auth OK");
        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(LED_PIN, LOW);
      } else {
        Serial.println("❌ Invalid Input");
      }
    }
  }
};

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  NimBLEDevice::init("BondBand_Fresh");
  NimBLEServer *pServer = NimBLEDevice::createServer();

  NimBLEService *pService = pServer->createService(SERVICE_UUID);
  NimBLECharacteristic *pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR
  );

  pCharacteristic->setCallbacks(new RXCallbacks());
  pService->start();

  NimBLEAdvertising *adv = NimBLEDevice::getAdvertising();
  adv->addServiceUUID(SERVICE_UUID);
  adv->start();

  Serial.println("✅ New BLE ready — connect and write AUTH_12345");
}

void loop() {
  delay(1000);
}
