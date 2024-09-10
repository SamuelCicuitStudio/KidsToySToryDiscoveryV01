#include <Arduino.h>
#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// I2S Amplifier (MAX98357AEW)
#define I2S_SD_MODE_PIN 5
#define I2S_BCLK_PIN 7
#define I2S_DIN_PIN 6

// SD Card Module
//Form real device
#define SD_MISO_PIN 42    // DATA0/MISO
#define SD_CLK_PIN 41     // CLK


#define SD_MOSI_PIN 39    // CMD/MOSI
#define SD_CS_PIN 38      // CS/DATA3

// Microphone Module (MAX9814ETD)
#define MIC_OUT_PIN 4     // MICOUT

//Form real device
#define MIC_GAIN_PIN 47   // GAINMIC
#define MIC_AR_PIN 48     // A/R



//LEDs
#define LED1_PIN 18
#define LED2_PIN 8

// Buttons (Pulled up)
#define BUTTON1_PIN 16
#define BUTTON2_PIN 17

#endif // PIN_CONFIG_H
