#include "EEPROMManager.h"

// Constructor
EEPROMManager::EEPROMManager() {
    initEEPROM();  // Initialize EEPROM during object creation
}

// Function to store a boolean in EEPROM
void EEPROMManager::storeBool(int addr, bool value) {
    EEPROM.write(addr, value);
    EEPROM.commit();  // Commit changes to EEPROM
    delay(200);  // Small delay for stability
}

// Function to read a boolean from EEPROM
bool EEPROMManager::readBool(int addr) {
    return EEPROM.read(addr);  // Return the boolean value stored at the specified address
}

// Function to store a string in EEPROM
void EEPROMManager::storeString(int startingAddress, String data) {
    byte len = data.length();  // Get the length of the string
    EEPROM.write(startingAddress, len);  // Write the length of the string
    
    for (int i = 0; i < len; i++) {
        EEPROM.write(startingAddress + 1 + i, data[i]);  // Write each character of the string
    }

    EEPROM.commit();  // Commit changes to EEPROM
    delay(1000);
}

// Function to read a string from EEPROM
String EEPROMManager::readString(int addrOffset) {
    int newStrLen = EEPROM.read(addrOffset);  // Read the length of the stored string
    char data[newStrLen + 1];  // Create a character array to hold the string data
    
    for (int i = 0; i < newStrLen; i++) {
        data[i] = EEPROM.read(addrOffset + 1 + i);  // Read each character of the string
    }
    data[newStrLen] = '\0';  // Null-terminate the character array
    
    return String(data);  // Convert the character array to a String object
}

// Function to store a uint16_t in EEPROM
void EEPROMManager::storeInt(int address, int number) {
    byte byte1 = number >> 8;
    byte byte2 = number & 0xFF;
    EEPROM.write(address, byte1);
    EEPROM.write(address + 1, byte2);
    EEPROM.commit();  // Commit changes to EEPROM
    delay(1000);
}

// Function to read a uint16_t from EEPROM
uint16_t EEPROMManager::readInt(int address) {
    byte byte1 = EEPROM.read(address);
    byte byte2 = EEPROM.read(address + 1);
    return (byte1 << 8) + byte2;
}

// Function to store a uint32_t in EEPROM
void EEPROMManager::storeUInt32(int address, uint32_t number) {
    byte byte1 = (number >> 24) & 0xFF;
    byte byte2 = (number >> 16) & 0xFF;
    byte byte3 = (number >> 8) & 0xFF;
    byte byte4 = number & 0xFF;

    EEPROM.write(address, byte1);
    EEPROM.write(address + 1, byte2);
    EEPROM.write(address + 2, byte3);
    EEPROM.write(address + 3, byte4);
    EEPROM.commit();  // Commit changes to EEPROM
    delay(1000);
}

// Function to read a uint32_t from EEPROM
uint32_t EEPROMManager::readUInt32(int address) {
    byte byte1 = EEPROM.read(address);
    byte byte2 = EEPROM.read(address + 1);
    byte byte3 = EEPROM.read(address + 2);
    byte byte4 = EEPROM.read(address + 3);

    return (byte1 << 24) + (byte2 << 16) + (byte3 << 8) + byte4;
}

// Function to initialize EEPROM
void EEPROMManager::initEEPROM() {
    start:;
        if (EEPROM.begin(EEPROM_SIZE)) {
            
            Serial.println("EEPROM initialized successfully.");
        } else {
            Serial.println("EEPROM initialization failed. Retrying...");
            delay(1000);  // Wait 1 second before retrying
            goto start;
        };
    
}

// Function to erase EEPROM
void EEPROMManager::eraseEEPROM() {
    Serial.println("Erasing EEPROM...");

    // Iterate through each address in the EEPROM and write 0 to clear it
    for (int i = 0; i < EEPROM_SIZE; i++) {
        EEPROM.write(i, 0);
    }

    // Commit the changes to EEPROM
    EEPROM.commit();

    Serial.println("EEPROM erased.");
}
