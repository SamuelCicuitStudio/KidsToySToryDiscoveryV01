#include "RecordingManager.h"

RecordingManager::RecordingManager() :  _recording(false) {}

bool RecordingManager::begin() {
    if (!SD.begin(_csPin)) {
        Serial.println("SD initialization failed!");
        return false;
    }
    return true;
}

bool RecordingManager::startRecording(const char *filename) {
    if (_recording) {
        Serial.println("Recording already in progress.");
        return false;
    }

    _file = SD.open(filename, FILE_WRITE);
    if (!_file) {
        Serial.println("Failed to open file for writing.");
        return false;
    }

    _recording = true;
    _startMillis = millis();

    // Clear buffer
    memset(_buffer, 0, sizeof(_buffer));

    Serial.println("Recording started.");

    // Start recording process
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        if (millis() - _startMillis >= 1000) { // Check if 1 second has passed
            _buffer[i] = analogRead(_micPin) - 2048; // Center the 12-bit value around 0
            _startMillis = millis();
        }
    }

    // Stop recording automatically after duration
    stopRecording();

    return true;
}

void RecordingManager::stopRecording() {
    if (!_recording) {
        Serial.println("No recording in progress.");
        return;
    }

    // Write WAV header
    writeWavHeader(_file);

    // Write audio data
    _file.write(reinterpret_cast<const uint8_t*>(_buffer), sizeof(_buffer));

    _file.close();
    _recording = false;

    Serial.println("Recording stopped and file saved.");
}

void RecordingManager::writeWavHeader(File &file) {
    struct {
        char riff[4];
        uint32_t chunkSize;
        char wave[4];
        char fmt[4];
        uint32_t subchunk1Size;
        uint16_t audioFormat;
        uint16_t numChannels;
        uint32_t sampleRate;
        uint32_t byteRate;
        uint16_t blockAlign;
        uint16_t bitsPerSample;
        char data[4];
        uint32_t dataSize;
    } wavHeader;

    wavHeader.riff[0] = 'R'; wavHeader.riff[1] = 'I'; wavHeader.riff[2] = 'F'; wavHeader.riff[3] = 'F';
    wavHeader.wave[0] = 'W'; wavHeader.wave[1] = 'A'; wavHeader.wave[2] = 'V'; wavHeader.wave[3] = 'E';
    wavHeader.fmt[0] = 'f'; wavHeader.fmt[1] = 'm'; wavHeader.fmt[2] = 't'; wavHeader.fmt[3] = ' ';
    wavHeader.data[0] = 'd'; wavHeader.data[1] = 'a'; wavHeader.data[2] = 't'; wavHeader.data[3] = 'a';

    wavHeader.subchunk1Size = 16;
    wavHeader.audioFormat = 1; // PCM
    wavHeader.numChannels = 1; // Mono
    wavHeader.sampleRate = SAMPLE_RATE;
    wavHeader.bitsPerSample = 16;
    wavHeader.byteRate = SAMPLE_RATE * wavHeader.numChannels * wavHeader.bitsPerSample / 8;
    wavHeader.blockAlign = wavHeader.numChannels * wavHeader.bitsPerSample / 8;
    wavHeader.dataSize = BUFFER_SIZE * wavHeader.blockAlign;
    wavHeader.chunkSize = 36 + wavHeader.dataSize;

    file.write(reinterpret_cast<const uint8_t*>(&wavHeader), sizeof(wavHeader));
}
