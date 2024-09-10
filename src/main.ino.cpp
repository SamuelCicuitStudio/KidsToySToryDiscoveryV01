# 1 "C:\\Users\\hp\\AppData\\Local\\Temp\\tmpydhu9_k3"
#include <Arduino.h>
# 1 "D:/Freelancer/JOBS/@sebbary/TestCode/KidsToySToryDiscoveryV01/src/main.ino"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>
#include "WifiManager.h"
#include "buttonManager.h"
#include "PeripheralsInit.h"





WifiManager wifiManager;
ButtonManager buttonManager;
PeripheralsInit peripherals;
MicrophoneManager Mic;
EEPROMManager EePROMManager;
void setup();
void loop();
#line 18 "D:/Freelancer/JOBS/@sebbary/TestCode/KidsToySToryDiscoveryV01/src/main.ino"
void setup() {
  Serial.begin(115200);
  Serial.println("\n\n");
  Serial.println("*********************************");
  Serial.println("*      Initializing EEPROM      *");
  Serial.println("*********************************");
  _EepromInit;
  Serial.println("*********************************");
  Serial.println("*       Initializing SD card    *");
  Serial.println("*********************************");
  _SdCardInit;
  Serial.println("*********************************");
  Serial.println("*      Initializing Button      *");
  Serial.println("*********************************");
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

  wifiManager.begin();
  Serial.println("*********************************");
  Serial.println("*  Setup done, entering loop..  *");
  Serial.println("*********************************");
}

void loop() {
delay(10);
  while(EePROMManager.readBool(ADDR_CONFIG_FLAG)){
  buttonManager.handleButtonPressPulledUp();
  }
}