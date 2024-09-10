#include <Arduino.h>
#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// I2S Amplifier (MAX98357AEW)
#define I2S_SD_MODE_PIN 27 //5
#define I2S_BCLK_PIN 25//7
#define I2S_DIN_PIN 26//6

// SD Card Module
//Form real device
//#define SD_MISO_PIN GPIO_NUM_42    // DATA0/MISO
//#define SD_CLK_PIN GPIO_NUM_41     // CLK

//for test device
#define SD_MISO_PIN 23//36    // DATA0/MISO
#define SD_CLK_PIN 22//37     // CLK

#define SD_MOSI_PIN 21//39    // CMD/MOSI
#define SD_CS_PIN 19//38      // CS/DATA3

// Microphone Module (MAX9814ETD)
#define MIC_OUT_PIN 5//4     // MICOUT

//Form real device
//#define MIC_GAIN_PIN GPIO_NUM_47   // GAINMIC
//#define MIC_AR_PIN GPIO_NUM_48     // A/R

//for test device
#define MIC_GAIN_PIN 12//32   // GAINMIC
#define MIC_AR_PIN 13//35     // A/R

// LEDs
#define LED1_PIN 18//18
#define LED2_PIN 4//8

// Buttons (Pulled up)
#define BUTTON1_PIN  0//16 real device
#define BUTTON2_PIN 2//17

#endif // PIN_CONFIG_H
