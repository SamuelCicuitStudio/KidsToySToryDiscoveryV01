#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "DeviceConfig.h"
#include "pin_config.h"
#include "EEPROMManager.h"
#include "WifiManager.h"

class ButtonManager {
public:
    // Function prototypes
    uint8_t handleButtonPressPulledUp();
    uint8_t handleButtonPressPulledDown();
    void resetDevice();
private:
    EEPROMManager* EepromManager;  // Pointer to EEPROMManager instance
    WifiManager* wifiManager;
};

#endif // BUTTON_MANAGER_H
