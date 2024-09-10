
#ifndef RECORDING_MANAGER_H
#define RECORDING_MANAGER_H

#include <SD.h>
#include <SPI.h>
#include "pin_config.h"

#define SAMPLE_RATE 16000        // Sampling rate in Hz
#define DURATION_SECONDS 10     // Duration of recording in seconds
#define BUFFER_SIZE (SAMPLE_RATE * DURATION_SECONDS)

class RecordingManager {
public:
    RecordingManager();
    bool begin();
    bool startRecording(const char *filename);
    void stopRecording();

private:
    int _csPin = SD_CS_PIN;
    int _micPin = MIC_OUT_PIN;
    File _file;
    short _buffer[BUFFER_SIZE];
    unsigned long _startMillis;
    bool _recording;
    void writeWavHeader(File &file);
};

#endif
