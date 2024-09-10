#include <Arduino.h>
#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// I2S Amplifier (MAX98357AEW)
#define I2S_SD_MODE_PIN GPIO_NUM_5
#define I2S_BCLK_PIN GPIO_NUM_7
#define I2S_DIN_PIN GPIO_NUM_6

// SD Card Module
//Form real device
#define SD_MISO_PIN GPIO_NUM_42    // DATA0/MISO
#define SD_CLK_PIN GPIO_NUM_41     // CLK


#define SD_MOSI_PIN GPIO_NUM_39    // CMD/MOSI
#define SD_CS_PIN GPIO_NUM_38      // CS/DATA3

// Microphone Module (MAX9814ETD)
#define MIC_OUT_PIN GPIO_NUM_4     // MICOUT

//Form real device
#define MIC_GAIN_PIN GPIO_NUM_47   // GAINMIC
#define MIC_AR_PIN GPIO_NUM_48     // A/R



//LEDs
#define LED1_PIN GPIO_NUM_18
#define LED2_PIN GPIO_NUM_8

// Buttons (Pulled up)
#define BUTTON1_PIN GPIO_NUM_16
#define BUTTON2_PIN GPIO_NUM_17

#endif // PIN_CONFIG_H
