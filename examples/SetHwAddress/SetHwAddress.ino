/**
 * @file SetDeviceID.ino
 * @brief Example of using the AM4096 encoder to change its ID.
 */

#include <Wire.h>
#include <AM4096.h>

// Constants for configuration settings
const uint16_t DEVICE_ADDRESS = 0x00;
const uint16_t NEW_DEVICE_ADDRESS = 0x5A;  // New device address

// Create an instance of the AM4096 encoder class
AM4096 encoder(DEVICE_ADDRESS); // device address

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        // Wait for serial port to connect
    }
    Serial.println(F("AM4096 SetHwAddress Example"));
    
    Wire.begin();
    
    // Initialize the communication with the encoder
    if (encoder.init() != 0) {
        Serial.println("Device ID not correct");
        while (1) {
            // Halt the program if device ID is incorrect
        }
    } else {
        Serial.println("Device ID correct");
    }
    
    if (!encoder.setNewHwAddr(NEW_DEVICE_ADDRESS)) {
        Serial.println("Cannot set new ID");
    }
}

void loop() {
    // Your loop code (if needed)
}
