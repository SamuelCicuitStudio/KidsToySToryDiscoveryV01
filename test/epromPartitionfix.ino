#include <EEPROM.h>
#include <nvs_flash.h>

void eraseNVS() {
  // Attempt to erase the NVS partition
  esp_err_t err = nvs_flash_erase();
  if (err == ESP_OK) {
    Serial.println("NVS erased successfully");
  } else {
    Serial.printf("Error erasing NVS: %s\n", esp_err_to_name(err));
  }

  // Reinitialize the NVS partition
  err = nvs_flash_init();
  if (err == ESP_OK) {
    Serial.println("NVS initialized successfully");
  } else {
    Serial.printf("Error initializing NVS: %s\n", esp_err_to_name(err));
  }
}

void setup() {
  // Start serial communication
  Serial.begin(115200);
  delay(1000);

  // Erase and reinitialize the NVS partition
  eraseNVS();

  // Initialize EEPROM with a size of 512 bytes
  if (!EEPROM.begin(512)) {
    Serial.println("Failed to initialize EEPROM");
  } else {
    Serial.println("EEPROM initialized successfully");
  }

  // Optional: Write some data to EEPROM to test it
  EEPROM.write(0, 42);  // Example: Write the value 42 to EEPROM address 0
  EEPROM.commit();      // Commit changes to EEPROM

  // Verify the data was written successfully
  int value = EEPROM.read(0);
  Serial.printf("Read value from EEPROM: %d\n", value);
}

void loop() {
  // Nothing to do in loop
}
