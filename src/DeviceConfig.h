#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H

#include <driver/adc.h>  // Include the ESP32 ADC driver for analog-to-digital conversion

/**************************************************************************************************
 * Device Configuration Constants
 **************************************************************************************************/

// ADC (Analog-to-Digital Converter) Configuration
// Configures the width of ADC conversions in bits (12-bit resolution).
#define ADC_WIDTH ADC_WIDTH_BIT_12

// ADC Attenuation Configuration
// Sets the attenuation level for the ADC to define the input voltage range.
// ADC_ATTEN_DB_0: No attenuation (voltage range 0 - 1.1V).
#define ADC_ATTEN ADC_ATTEN_DB_0

// File Path for Configuration Storage
// Path where the device configuration file is stored.
#define CONFIG_PATH "/Config.json"

/**************************************************************************************************
 * Default Credentials
 **************************************************************************************************/

// Default Hotspot Credentials
// These credentials are used if no custom hotspot credentials are set.
#define DEFAULT_HOTSPOT_NAME "TestSebWifiHotspot"
#define DEFAULT_HOTSPOT_PASS "1234567890"

// Default Wi-Fi Credentials
// These credentials are used if no custom Wi-Fi credentials are set.
#define DEFAULT_WIFI_NAME "TestSebWifi"
#define DEFAULT_WIFI_PASS "1234567890"

/**************************************************************************************************
 * EEPROM Configuration
 **************************************************************************************************/

// EEPROM Size
// Defines the size of the EEPROM in bytes.
#define EEPROM_SIZE 64

// EEPROM Address for Configuration Flag
// Address in EEPROM to store the configuration flag.
#define ADDR_CONFIG_FLAG 18

/**************************************************************************************************
 * Button Configuration
 **************************************************************************************************/

// Button Pin Bitmask
// Defines the bitmask for button pin configuration.
#define BUTTON_PIN_BITMASK 0x14  // 2^2 + 2^4 in hex

// Button Press Duration and Delay
// Defines the durations for long and short button presses.
#define LONGPRESSDURATION 2500
#define SHORTPRESSDELAY 200
#define DEBOUNCE 50  // Debounce time for button presses

#endif // DEVICE_CONFIG_H



//platformio.exe run --target erase