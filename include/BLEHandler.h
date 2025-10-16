/*#ifndef BLE_HANDLER_H
#define BLE_HANDLER_H

#include <NimBLEDevice.h>

class BLEHandler {
  public:
    BLEHandler();
    void begin();
    void loop();
    bool isConnected();
    void setAuthToken(String token);

    static bool deviceConnected;
    static String validToken;
};

#endif
*/