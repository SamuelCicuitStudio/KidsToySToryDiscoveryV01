#include "buttonManager.h"

unsigned long pressStartTime ; // Track the button press start time
uint8_t ButtonManager::handleButtonPressPulledUp() {
    pressStartTime = millis();

    while (!digitalRead(BUTTON1_PIN)) {
        delay(DEBOUNCE);
        
        while (1) {
            if (millis() - pressStartTime > SHORTPRESSDELAY) {
                while (!digitalRead(BUTTON1_PIN)) {
                    if (millis() - pressStartTime > LONGPRESSDURATION) {
                        Serial.println("long press!");
                        Serial.println("Resetting the Device!");
                        EepromManager->storeBool(ADDR_CONFIG_FLAG, true); // Set true a flag to reset
                        resetDevice(); // Function to reset the device
                        return 0;
                    }
                }
                return 2;
            }
            
            if (digitalRead(BUTTON1_PIN)) {
                pressStartTime = millis();
                break;
            }
        }
    }

    while (digitalRead(BUTTON1_PIN)) {
        delay(DEBOUNCE);
        
        while (1) {
            if (millis() - pressStartTime > SHORTPRESSDELAY) {
                return 2;
            }
            
            if (!digitalRead(BUTTON1_PIN)) {
                pressStartTime = millis();
                break;
            }
        }
    }

    while (!digitalRead(BUTTON1_PIN)) {
        delay(DEBOUNCE);
        
        while (1) {
            if (millis() - pressStartTime > SHORTPRESSDELAY) {
                return 2;
            }
            
            if (digitalRead(BUTTON1_PIN)) {
                pressStartTime = millis();
                break;
            }
        }
    }

    while (digitalRead(BUTTON1_PIN)) {
        delay(DEBOUNCE);
        
        while (1) {
            if (millis() - pressStartTime > SHORTPRESSDELAY) {
                return 2;
            }
            
            if (!digitalRead(BUTTON1_PIN)) {
                pressStartTime = millis();
                break;
            }
        }
    }

    while (!digitalRead(BUTTON1_PIN)) {
        delay(DEBOUNCE);
        
        while (1) {
            if (millis() - pressStartTime > SHORTPRESSDELAY) {
                return 2;
            }
            
            if (!digitalRead(BUTTON1_PIN)) {
                pressStartTime = millis();
                break;
            }
        }
    }

    delay(DEBOUNCE);
    Serial.println("Button pressed. Starting AP mode.");
    EepromManager->storeBool(ADDR_CONFIG_FLAG, true); // Restart the device in AP mode
    delay(2000);
    esp_restart(); // Restart the device

    return 1;
}

uint8_t ButtonManager::handleButtonPressPulledDown() {
    pressStartTime = millis();

    while (digitalRead(BUTTON1_PIN)) {
        delay(DEBOUNCE);
        
        while (1) {
            if (millis() - pressStartTime > SHORTPRESSDELAY) {
                while (digitalRead(BUTTON1_PIN)) {
                    if (millis() - pressStartTime > LONGPRESSDURATION) {
                        Serial.println("long press!");
                        Serial.println("Resetting the Device!");
                        EepromManager->storeBool(ADDR_CONFIG_FLAG, true); // Set true a flag to reset
                        resetDevice(); // Function to reset the device
                        return 0;
                    }
                }
                return 2;
            }
            
            if (!digitalRead(BUTTON1_PIN)) {
                pressStartTime = millis();
                break;
            }
        }
    }

    while (!digitalRead(BUTTON1_PIN)) {
        delay(DEBOUNCE);
        
        while (1) {
            if (millis() - pressStartTime > SHORTPRESSDELAY) {
                return 2;
            }
            
            if (digitalRead(BUTTON1_PIN)) {
                pressStartTime = millis();
                break;
            }
        }
    }

    while (digitalRead(BUTTON1_PIN)) {
        delay(DEBOUNCE);
        
        while (1) {
            if (millis() - pressStartTime > SHORTPRESSDELAY) {
                return 2;
            }
            
            if (!digitalRead(BUTTON1_PIN)) {
                pressStartTime = millis();
                break;
            }
        }
    }

    while (!digitalRead(BUTTON1_PIN)) {
        delay(DEBOUNCE);
        
        while (1) {
            if (millis() - pressStartTime > SHORTPRESSDELAY) {
                return 2;
            }
            
            if (digitalRead(BUTTON1_PIN)) {
                pressStartTime = millis();
                break;
            }
        }
    }

    while (digitalRead(BUTTON1_PIN)) {
        delay(DEBOUNCE);
        
        while (1) {
            if (millis() - pressStartTime > SHORTPRESSDELAY) {
                return 2;
            }
            
            if (!digitalRead(BUTTON1_PIN)) {
                pressStartTime = millis();
                break;
            }
        }
    }

    delay(DEBOUNCE);
    Serial.println("Button pressed. Starting AP mode.");
    EepromManager->storeBool(ADDR_CONFIG_FLAG, true); // Restart the device in AP mode
    delay(2000);
    esp_restart(); // Restart the device

    return 1;
}


  // Function to reset the device
void ButtonManager::resetDevice() {
    Serial.println("Device Reset");
    DynamicJsonDocument doc(1024);
        doc["wifiSSID"] = DEFAULT_WIFI_NAME;         // Default WiFi SSID
        doc["wifiPassword"] = DEFAULT_WIFI_PASS;      // Default WiFi Password
        doc["hotspotSSID"] = DEFAULT_HOTSPOT_NAME; // Default Hotspot SSID
        doc["hotspotPassword"] = DEFAULT_HOTSPOT_PASS; // Default Hotspot Password
        doc["mode"] = "hotspot";                 // Default to hotspot mode

        // Serialize and save the default config to the file
        String defaultConfig;
        serializeJson(doc, defaultConfig);
        wifiManager->writeConfig(defaultConfig);

        EepromManager->eraseEEPROM();
    // Insert logic for resetting the device, such as clearing config, etc.
}