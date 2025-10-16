#include <Arduino.h>
#include <NimBLEDevice.h>

#define LED_PIN 2

// BLE service and characteristic UUIDs
#define SERVICE_UUID        "12345678-90ab-cdef-1234-567890abcdef"
#define CHARACTERISTIC_UUID "abcdef01-1234-5678-90ab-cdef12345678"

class RXCallbacks : public NimBLECharacteristicCallbacks {
  void onWrite(NimBLECharacteristic *pCharacteristic) {
    std::string rxValue = pCharacteristic->getValue();
    Serial.println("⚙️ onWrite callback fired");
    if (rxValue.length() > 0) {
      Serial.print("Received: ");
      Serial.println(rxValue.c_str());
      if (rxValue == "AUTH_12345") {
        Serial.println("✅ Auth OK");
        digitalWrite(LED_PIN, HIGH);
        delay(200);
        digitalWrite(LED_PIN, LOW);
      } else {
        Serial.println("❌ Wrong input");
      }
    }
  }
};

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Booting BLE...");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  NimBLEDevice::init("BondBand_Test");
  NimBLEServer *pServer = NimBLEDevice::createServer();

  // Create BLE service
  NimBLEService *pService = pServer->createService(SERVICE_UUID);

  // Create characteristic with WRITE | WRITE_NR
  NimBLECharacteristic *pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR);

  // Attach callback to the characteristic
  pCharacteristic->setCallbacks(new RXCallbacks());

  // Start service
  pService->start();

  // Start advertising
  NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();

  Serial.println("✅ BLE ready — open LightBlue and connect.");
  Serial.println("Write to the characteristic to test.");
}

void loop() {
  delay(1000);
}


/*hello this is a comment */
