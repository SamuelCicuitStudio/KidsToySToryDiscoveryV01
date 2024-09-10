#include "MicrophoneManager.h"

/**
 * @brief Constructor for MicrophoneManager class.
 * Initializes the microphone control pins.
 */
MicrophoneManager::MicrophoneManager() {
  configureMic();
}

/**
 * @brief Initialize the microphone with default settings.
 * Sets default gain and auto-recovery configurations.
 */
void MicrophoneManager::init() {
    configureMic();
}

/**
 * @brief Configures the microphone's gain and auto-recovery based on default values.
 * By default, sets high gain and disables auto-recovery.
 */
void MicrophoneManager::configureMic() {
    // Configure microphone gain and auto-recovery settings
    digitalWrite(MIC_GAIN_PIN, HIGH); // Set high gain for the microphone
    digitalWrite(MIC_AR_PIN, LOW);    // Disable auto-recovery mode
   
    // Configure ADC width (e.g., ADC_WIDTH_BIT_12 for 12-bit resolution)
    esp_err_t err = adc1_config_width(ADC_WIDTH);
    if (err != ESP_OK) {
        Serial.printf("Failed to configure ADC width: %s\n", esp_err_to_name(err));
        return;
    }
   err = adc1_config_channel_atten((adc1_channel_t)MIC_OUT_PIN, ADC_ATTEN);
    if (err != ESP_OK) {
        Serial.printf("Failed to configure ADC channel attenuation: %s\n", esp_err_to_name(err));
        return;
    }
     Serial.println("     Microphone initialized.     ");
     Serial.println("*********************************");

}

/**
 * @brief Set the gain for the microphone.
 * @param highGain If true, sets the gain to high; otherwise, sets to low.
 */
void MicrophoneManager::setGain(bool highGain) {
    if (highGain) {
        digitalWrite(MIC_GAIN_PIN, HIGH);
        Serial.println("Microphone gain set to high.");
    } else {
        digitalWrite(MIC_GAIN_PIN, LOW);
        Serial.println("Microphone gain set to low.");
    }
}

/**
 * @brief Enable or disable auto-recovery mode for the microphone.
 * @param enable If true, enables auto-recovery; otherwise, disables it.
 */
void MicrophoneManager::setAutoRecovery(bool enable) {
    if (enable) {
        digitalWrite(MIC_AR_PIN, HIGH);
        Serial.println("Auto-recovery enabled.");
    } else {
        digitalWrite(MIC_AR_PIN, LOW);
        Serial.println("Auto-recovery disabled.");
    }
}

/**
 * @brief Read the current analog value from the microphone output.
 * @return Analog value from the microphone.
 */
int MicrophoneManager::readMicOutput() {
    int micValue = analogRead(MIC_OUT_PIN);
    Serial.print("Microphone output: ");
    Serial.println(micValue);
    return micValue;
}
