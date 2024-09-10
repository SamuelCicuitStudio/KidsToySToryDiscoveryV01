#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include <EEPROM.h>
#include "DeviceConfig.h"
#include <Arduino.h>
#define _EepromInit { if (!EEPROM.begin(EEPROM_SIZE)) {Serial.println("Failed to initialize EEPROM");while (1) {delay(10); }} else {Serial.println("EEPROM initialized successfully");}}
class EEPROMManager {
public:
    EEPROMManager();  // Constructor to initialize EEPROM

    // Boolean operations
    void storeBool(int addr, bool value);  // Store boolean in EEPROM
    bool readBool(int addr);  // Read boolean from EEPROM

    // String operations
    void storeString(int startingAddress, String data);  // Store string in EEPROM
    String readString(int addrOffset);  // Read string from EEPROM

    // Integer operations
    void storeInt(int address, int number);  // Store uint16_t in EEPROM
    uint16_t readInt(int address);  // Read uint16_t from EEPROM

    // Unsigned Integer (32-bit) operations
    void storeUInt32(int address, uint32_t number);  // Store uint32_t in EEPROM
    uint32_t readUInt32(int address);  // Read uint32_t from EEPROM

    // EEPROM Initialization
    void initEEPROM();  // Initialize EEPROM
    void eraseEEPROM();  // Erase EEPROM contents


};

#endif // EEPROM_MANAGER_H