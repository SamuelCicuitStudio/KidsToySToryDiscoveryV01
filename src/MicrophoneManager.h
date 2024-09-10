#ifndef MICROPHONE_MANAGER_H
#define MICROPHONE_MANAGER_H

#include <Arduino.h>
#include "pin_config.h"
#include "DeviceConfig.h"


class MicrophoneManager {
public:

    MicrophoneManager();// Constructor
    void init();// Initialize the microphone
    void setGain(bool highGain);// Set the microphone gain (high or low gain)
    void setAutoRecovery(bool enable); // Enable or disable auto-recovery
    int readMicOutput(); // Read the microphone output (analog value)
        // Internal methods to set gain and auto-recovery
    void configureMic();
    
private:


};

#endif // MICROPHONE_MANAGER_H
