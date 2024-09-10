/**
 * @file PeripheralsInit.h
 * @brief Header file for the PeripheralsInit class, which manages initialization and 
 *        I2S audio playback for ESP32 peripherals.
 */

#ifndef PERIPHERALS_INIT_H
#define PERIPHERALS_INIT_H

#include <Arduino.h>
#include "WAVFileReader.h"
#include "SinWaveGenerator.h"
#include "I2SOutput.h"
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "driver/i2s.h"
#include "pin_config.h"
#include "MicrophoneManager.h"

#define _BtInit {pinMode(BUTTON1_PIN, INPUT);pinMode(BUTTON2_PIN, INPUT);}
#define _LedInit {pinMode(LED1_PIN, OUTPUT);pinMode(LED2_PIN, OUTPUT);}
class PeripheralsInit {
public:
    // Constructor
    PeripheralsInit();

    void initMicrophone();
    // Function to start I2S audio playback
    void startI2SPlayback(const char* wavFilePath);
    // Initialization functions for individual peripherals
    void initI2S();
    void initSDCard();
    void initLEDs();
    void initButtons();

private:
    // I2S configuration and audio playback
    i2s_pin_config_t i2sPins;       // I2S pin configuration
    I2SOutput* output;              // Pointer to I2S output object
    SampleSource* sampleSource;     // Pointer to WAV file sample source
    MicrophoneManager* microphoneManager;
   
};

#endif // PERIPHERALS_INIT_H
