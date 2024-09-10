#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>
#include "WifiManager.h"
#include "buttonManager.h"



// Create an instance of the WiFiManager
WifiManager wifiManager;
ButtonManager buttonManager;
 ;
void setup() {
  
  Serial.begin(115200);// Initialize serial communication
  wifiManager.begin();// Initialize WiFiManager
}

void loop() {
  delay(1);// Nothing to do here
  buttonManager.handleButtonPressPulledUp();
}
