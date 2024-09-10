#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>
#include "WifiManager.h"
#include "buttonManager.h"
#include "PeripheralsInit.h"




// Create an instance of the WiFiManager
WifiManager wifiManager;
ButtonManager buttonManager;
PeripheralsInit peripherals;
MicrophoneManager Mic;
EEPROMManager EePROMManager; 
void setup() {
  Serial.begin(115200);// Initialize serial communication
  Serial.println("\n\n");
  Serial.println("*********************************");
  Serial.println("*      Initializing EEPROM      *");
  Serial.println("*********************************");
  _EepromInit;
  Serial.println("*********************************");
  Serial.println("*      Initializing Button      *");
  Serial.println("*********************************");
  _BtInit;
  Serial.println("*********************************");
  Serial.println("*      Initializing LEDS        *");
  Serial.println("*********************************");
  _LedInit;
  Serial.println("*********************************");
  Serial.println("*       Initializing Mic        *");
  Serial.println("*********************************");
  _MicInit;
 
  peripherals.initLEDs();
  peripherals.initButtons();
  Mic.init();
 //peripherals.initSDCard(); 
  wifiManager.begin();// Initialize WiFiManager
  Serial.println("*********************************");
  Serial.println("*  Setup done, entering loop..  *");
  Serial.println("*********************************");
}

void loop() {

  while(EePROMManager.readBool(ADDR_CONFIG_FLAG)){
  buttonManager.handleButtonPressPulledUp();
  }
}
