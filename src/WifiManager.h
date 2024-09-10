#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include "WiFiCredentialHTML.h"
#include "DeviceConfig.h"
#include "EEPROMManager.h"
#include "PeripheralsInit.h"

class WifiManager {
public:
    WifiManager();
    void begin();
    void saveCredentials(const String& ssid, const String& password);
    void saveConfig(const String& mode, const String& hotspotSSID, const String& hotspotPassword);
    void writeConfig(const String& json);
    void restart(uint8_t sec);
    EEPROMManager* EePROMManager;
    PeripheralsInit peripherals;

private:
    AsyncWebServer server;
    
    void setupServer();
    void handleRoot(AsyncWebServerRequest *request);
    void handleSaveCredentials(AsyncWebServerRequest *request);
    void handleSaveConfig(AsyncWebServerRequest *request);
    String readConfig();
    void startHotspot();
    String loadConfigValue(const String& key);
    void saveConfigValue(const String& key, const String& value);
    void connectWiFiOrStartHotspot();

};

#endif // WIFIMANAGER_H
