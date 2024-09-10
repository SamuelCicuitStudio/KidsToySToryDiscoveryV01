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
  Serial.println("*       Initializing SD card    *");
  Serial.println("*********************************");
 /* _SdCardInit;
  Serial.println("*********************************");
  Serial.println("*      Initializing Button      *");
  Serial.println("*********************************");*/
  _BtInit;
  peripherals.initButtons();
  Serial.println("*********************************");
  Serial.println("*      Initializing LEDS        *");
  Serial.println("*********************************");
  _LedInit;
  peripherals.initLEDs();
  Serial.println("*********************************");
  Serial.println("*       Initializing Mic        *");
  Serial.println("*********************************");
  _MicInit;
  Mic.init();
 
  wifiManager.begin();// Initialize WiFiManager
  Serial.println("*********************************");
  Serial.println("*  Setup done, entering loop..  *");
  Serial.println("*********************************");
}

void loop() {
//delay(1); 
// buttonManager.handleButtonPressPulledUp();

}
