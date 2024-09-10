/**
 * @file PeripheralsInit.cpp
 * @brief This file contains the PeripheralsInit class, which is responsible for initializing
 *        all peripherals (I2S, SD card, microphone, LEDs, and buttons) and managing I2S playback.
 */

#include "PeripheralsInit.h"

/**
 * @brief Constructor for the PeripheralsInit class.
 *        This constructor initializes member variables and prepares the ESP32 peripherals.
 */
PeripheralsInit::PeripheralsInit(){  
    // Initialize other peripherals
    //initButtons();
    //initLEDs();
    //initMicrophone();
    //initSDCard();
    //initI2S();
}

/**
 * @brief Initializes the I2S interface with the specified pins.
 * This function sets up the necessary pins for the I2S amplifier (MAX98357AEW).
 */
void PeripheralsInit::initI2S() {
    // Define the I2S pins
    i2sPins = {
        .bck_io_num = I2S_BCLK_PIN,      // Bit clock line
        .ws_io_num = I2S_SD_MODE_PIN,    // Word select line (LRCK)
        .data_out_num = I2S_DIN_PIN,     // Data output pin
        .data_in_num = I2S_PIN_NO_CHANGE // No data input needed
    };
}

/**
 * @brief Starts playback of a WAV file via the I2S interface.
 * This function opens the WAV file using the `WAVFileReader`, then starts streaming
 * the audio file to the I2S amplifier.
 * 
 * @param wavFilePath The file path of the WAV file to be played (e.g., "/sample.wav").
 */
void PeripheralsInit::startI2SPlayback(const char* wavFilePath) {
  sampleSource = new WAVFileReader(wavFilePath);

  Serial.println("Starting I2S Output");
  output = new I2SOutput();
  output->start(I2S_NUM_1, i2sPins, sampleSource);
}

/**
 * @brief Initializes the SD card module.
 * This function attempts to initialize the SD card interface and checks if the SD card
 * is inserted and ready for use.
 */
void PeripheralsInit::initSDCard() {
Serial.println("Use _SdCardInit instead.");
}

/**
 * @brief Initializes the MAX9814ETD microphone.
 * This function configures the microphone's output pin, gain control, and automatic
 * recovery settings.
 */
void PeripheralsInit::initMicrophone() {
microphoneManager->configureMic();
}

/**
 * @brief Initializes the LEDs.
 * This function configures the LED pins and turns them off by default.
 */
void PeripheralsInit::initLEDs() {
    // Turn off both LEDs initially
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    Serial.println("        LEDs initialized.         ");
     Serial.println("*********************************");
}

/**
 * @brief Initializes the buttons.
 * This function configures the button pins with internal pull-up resistors.
 */
void PeripheralsInit::initButtons() {
    // Configure buttons with internal pull-up resistors
     Serial.println("      Buttons initialized.       ");
     Serial.println("*********************************");
}
