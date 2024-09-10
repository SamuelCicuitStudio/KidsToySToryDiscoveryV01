#include "WifiManager.h"


WifiManager::WifiManager() : server(80) {}

void WifiManager::begin() {

    Serial.println("*********************************");
    Serial.println("*   Start Wifi Manager Config   *");

    if (!SPIFFS.begin(true)) {
    Serial.println("Failed to mount file system. Initializing file system.");
    if (!SPIFFS.format()) {
        Serial.println("Failed to format SPIFFS. Check the file system.");
        return;
    }
    if (!SPIFFS.begin()) {
        Serial.println("Failed to mount file system after formatting.");
        return;
    }
};
if(!EePROMManager->readBool(ADDR_CONFIG_FLAG)){
    startHotspot();
}else{
connectWiFiOrStartHotspot();
}    
}

void WifiManager::setupServer() {
    server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request){
        handleRoot(request);
    });

    server.on("/saveCredentials", HTTP_POST, [this](AsyncWebServerRequest *request){
        handleSaveCredentials(request);
    });

    server.on("/saveConfig", HTTP_POST, [this](AsyncWebServerRequest *request){
        handleSaveConfig(request);
    });

    server.begin();
}

void WifiManager::handleRoot(AsyncWebServerRequest *request) {
    String config = readConfig();
    String html = String(WiFiCredentialHTML);
    html.replace("{WIFI_SSID}", loadConfigValue("wifiSSID").isEmpty() ? "TestSebWifi" : loadConfigValue("wifiSSID"));
    html.replace("{WIFI_PASSWORD}", loadConfigValue("wifiPassword").isEmpty() ? "1234567890" : loadConfigValue("wifiPassword"));
    html.replace("{HOTSPOT_SSID}", loadConfigValue("hotspotSSID").isEmpty() ? "" : loadConfigValue("hotspotSSID"));
    html.replace("{HOTSPOT_PASSWORD}", loadConfigValue("hotspotPassword").isEmpty() ? "" : loadConfigValue("hotspotPassword"));
    html.replace("{MODE_CHECKED}", loadConfigValue("hotspotMode") == "true" ? "checked" : "");

    request->send(200, "text/html", html);
}

void WifiManager::handleSaveCredentials(AsyncWebServerRequest *request) {
    String ssid;
    String password;
    if (request->hasParam("ssid", true)) {
        ssid = request->getParam("ssid", true)->value();
    }
    if (request->hasParam("password", true)) {
        password = request->getParam("password", true)->value();
    }
    saveCredentials(ssid, password);
    // Send a response with JavaScript to show a pop-up
    String response = "<!DOCTYPE html>"
                      "<html>"
                      "<head><title>Config Saved</title></head>"
                      "<body>"
                      "<script>alert('Credentials saved, Restarting in 5 Sec.'); window.location.href='/';</script>"
                      "</body>"
                      "</html>";
    request->send(200, "text/html", response);;
    Serial.println("\nNew Credential Saved...");
    Serial.println("\nSave new Configurations to restart...");

}

void WifiManager::handleSaveConfig(AsyncWebServerRequest *request) {
    String mode;
    String hotspotSSID;
    String hotspotPassword;
    if (request->hasParam("mode", true)) {
        mode = request->getParam("mode", true)->value();
    }
    if (request->hasParam("hotspotSSID", true)) {
        hotspotSSID = request->getParam("hotspotSSID", true)->value();
    }
    if (request->hasParam("hotspotPassword", true)) {
        hotspotPassword = request->getParam("hotspotPassword", true)->value();
    }
    saveConfig(mode, hotspotSSID, hotspotPassword);
    // Send a response with JavaScript to show a pop-up
    String response = "<!DOCTYPE html>"
                      "<html>"
                      "<head><title>Config Saved</title></head>"
                      "<body>"
                      "<script>alert('Config saved'); window.location.href='/';</script>"
                      "</body>"
                      "</html>";
    request->send(200, "text/html", response);
    
    Serial.println("\nNew Configuration Saved...");
    EePROMManager->storeBool(ADDR_CONFIG_FLAG, true);//set true to go wifi first
    Serial.println("\nResetting Config flag...");
    EePROMManager->storeBool(ADDR_CONFIG_FLAG, true);//to set the flag for first time
    restart(5);//restarting in 5 seconds
}

void WifiManager::saveCredentials(const String& ssid, const String& password) {
    saveConfigValue("wifiSSID", ssid);
    saveConfigValue("wifiPassword", password);
}

void WifiManager::saveConfig(const String& mode, const String& hotspotSSID, const String& hotspotPassword) {
    DynamicJsonDocument doc(1024);
    doc["wifiSSID"] = loadConfigValue("wifiSSID").isEmpty() ? "TestSebWifi" : loadConfigValue("wifiSSID");
    doc["wifiPassword"] = loadConfigValue("wifiPassword").isEmpty() ? "1234567890" : loadConfigValue("wifiPassword");
    doc["hotspotSSID"] = hotspotSSID;
    doc["hotspotPassword"] = hotspotPassword;
    doc["hotspotMode"] = mode;

    String json;
    serializeJson(doc, json);
    writeConfig(json);
}

String WifiManager::readConfig() {
    /*if (!SPIFFS.begin(true)) {  // Auto-format if needed
        return "";  // Return empty if SPIFFS fails to mount
    }*/

    // Check if the config file exists
    if (!SPIFFS.exists(CONFIG_PATH)) {
        // Create default config if the file doesn't exist
        DynamicJsonDocument doc(1024);
        doc["wifiSSID"] = DEFAULT_WIFI_NAME;         // Default WiFi SSID
        doc["wifiPassword"] = DEFAULT_WIFI_PASS;      // Default WiFi Password
        doc["hotspotSSID"] = DEFAULT_HOTSPOT_NAME; // Default Hotspot SSID
        doc["hotspotPassword"] = DEFAULT_HOTSPOT_PASS;     // Default Hotspot Password
        doc["mode"] = "hotspot";                 // Default to hotspot mode

        // Serialize JSON and write to file
        String defaultConfig;
        serializeJson(doc, defaultConfig);
        writeConfig(defaultConfig);  // Write the default config to the file

        return defaultConfig;  // Return the default config
    }

    // Open and read the config file
    File file = SPIFFS.open(CONFIG_PATH, "r");
    if (!file || file.size() == 0) {
        return "";  // Return empty if file can't be opened or is empty
    }

    String config = file.readString();
    file.close();
    return config;
}


void WifiManager::writeConfig(const String& json) {
    if (!SPIFFS.begin()) {
        return;
    }

    File file = SPIFFS.open(CONFIG_PATH, "w");
    if (!file) {
        return;
    }

    file.print(json);
    file.close();
}

String WifiManager::loadConfigValue(const String& key) {
    String config = readConfig();

    // Check if the config file is empty or not initialized properly
    if (config.length() == 0 || config == "null") {
        // Set the default WiFi credentials and hotspot settings


        // Create a default JSON structure
        DynamicJsonDocument doc(1024);
        doc["wifiSSID"] = DEFAULT_WIFI_NAME;         // Default WiFi SSID
        doc["wifiPassword"] = DEFAULT_WIFI_PASS;      // Default WiFi Password
        doc["hotspotSSID"] = DEFAULT_HOTSPOT_NAME; // Default Hotspot SSID
        doc["hotspotPassword"] = DEFAULT_HOTSPOT_PASS; // Default Hotspot Password
        doc["mode"] = "hotspot";                 // Default to hotspot mode

        // Serialize and save the default config to the file
        String defaultConfig;
        serializeJson(doc, defaultConfig);
        writeConfig(defaultConfig);

        // Return the requested key from the default configuration
        return doc[key].as<String>();
    }

    // Parse the existing config and return the requested value
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, config);

    // Return the value for the given key, if it exists
    return doc[key].as<String>();
}


void WifiManager::saveConfigValue(const String& key, const String& value) {
    String config = readConfig();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, config);
    doc[key] = value;
    
    String json;
    serializeJson(doc, json);
    writeConfig(json);
}

void WifiManager::connectWiFiOrStartHotspot() {
    String ssid = loadConfigValue("wifiSSID");
    String password = loadConfigValue("wifiPassword");
    String mode = loadConfigValue("hotspotMode");
    Serial.println("*       Connecting to WiFi      *");
    Serial.println("*********************************");
    Serial.println("wifiSSID :");Serial.print(ssid);Serial.println();
    Serial.println("wifiPassword :");Serial.print(password);Serial.println();
    
    // Turn on the WiFi module and set to station mode
    Serial.println("Enabling WiFi STA...");
    WiFi.mode(WIFI_STA);//turnon the wifi module

    if (!ssid.isEmpty() && !password.isEmpty()) {
        WiFi.begin(ssid.c_str(), password.c_str());
        
        int attempts = 0;
        while (WiFi.status() != WL_CONNECTED && attempts < 20) {
            delay(500);
            Serial.print(".");
            attempts++;
        }

        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("\nSetting Config flag...");
            EePROMManager->storeBool(ADDR_CONFIG_FLAG, false);//to set the flag for first time
            restart(5);//restarting in 5 seconds
            
        } else {
            Serial.println("\n");
            Serial.println("**********************************");
            Serial.println("*       Connected to WiFi        *");
            Serial.println("*       IP Address:              *");
            Serial.println("--");Serial.print(WiFi.localIP());Serial.print("--");
            Serial.println("**********************************");
        }
    } else {
         Serial.println("\nSetting Config flag...");
            EePROMManager->storeBool(ADDR_CONFIG_FLAG, false);//to set the flag for first time
            restart(7);//restarting in 7 seconds
    }
}

void WifiManager::startHotspot() {
    Serial.println("*       Starting Hotspot        *");
    Serial.println("*********************************");

    // Optionally, configure the Access Point's IP settings
    IPAddress local_IP(192, 168, 4, 1);   // Set the local IP of the ESP32 (default is 192.168.4.1)
    IPAddress gateway(192, 168, 4, 1);    // Set the gateway IP (same as the local IP for this example)
    IPAddress subnet(255, 255, 255, 0);   // Set the subnet mask

    // Configure the network interface with the custom IP settings
    if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
        Serial.println("Failed to configure Access Point");
        return;
    }

    // Load the SSID and password from configuration
    String ssid = loadConfigValue("hotspotSSID");
    String password = loadConfigValue("hotspotPassword");

    // Start the Access Point with the loaded or default credentials
    if (!WiFi.softAP(ssid.c_str(), password.c_str())) {
        Serial.println("Failed to start Access Point");
        Serial.println("Writting default config in flash...");
        // Create a default JSON structure
        DynamicJsonDocument doc(1024);
        doc["wifiSSID"] = DEFAULT_WIFI_NAME;         // Default WiFi SSID
        doc["wifiPassword"] = DEFAULT_WIFI_PASS;      // Default WiFi Password
        doc["hotspotSSID"] = DEFAULT_HOTSPOT_NAME; // Default Hotspot SSID
        doc["hotspotPassword"] = DEFAULT_HOTSPOT_PASS; // Default Hotspot Password
        doc["mode"] = "hotspot";                 // Default to hotspot mode

        // Serialize and save the default config to the file
        String defaultConfig;
        serializeJson(doc, defaultConfig);
        writeConfig(defaultConfig);
        Serial.println("\nSetting Config flag...");
            EePROMManager->storeBool(ADDR_CONFIG_FLAG, false);//to set the flag for first time
            restart(7);//restarting in 7 seconds
        
    }

    // Print the IP address of the Access Point
            Serial.print("Access Point IP address: ");
            Serial.println("\n");
            Serial.println("**********************************");
            Serial.println("*       Connected to WiFi        *");
            Serial.println("*Access Point IP Address:");
            Serial.println(WiFi.softAPIP());Serial.println("   *");
            Serial.println("**********************************");
            delay(10);// Delay for stability
            setupServer();// Setup the server to handle requests
   
}

void WifiManager::restart(uint8_t sec){
    Serial.println("*********************************");
    Serial.println("*    Restartinng the Device     *");
    Serial.println("*********************************");
    Serial.println("Restarting in ");
    Serial.print(sec);
    Serial.print(" Sec ");
    Serial.println();
    int attempts = 0;
    while (attempts < sec) {
        delay(1000);
        Serial.print("*");
        attempts++;
     };
    esp_restart();//restart esp32
}