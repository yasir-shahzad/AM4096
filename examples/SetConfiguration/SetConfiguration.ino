/**
 * @file GetConfiguration.ino
 * @brief Example of using the AM4096 encoder to read configuration.
 */
#include <Wire.h>
#include <AM4096.h> // Include the header file

// Constants for configuration settings
const uint16_t RESOLUTION_12BIT = 1;
const uint16_t INDEX_POLARITY_ACTIVE_LOW = 1;

// Create an instance of the AM4096 encoder class
AM4096 encoder(0x5A); // I2C bus, device address

// Configuration data structure with initial settings
AM4096_config_data config = {
    .fields = {
        .Addr = RESOLUTION_12BIT,
        .Reg35 = INDEX_POLARITY_ACTIVE_LOW,
        .SSIcfg = 0x0000
    }
};

void setup() {
    // Initialize the communication with the encoder
    encoder.init();

    // Update the configuration
    bool configurationUpdated = encoder.updateConfiguration(&config, true);
    if (configurationUpdated) {
        Serial.println("Configuration updated");
    } else {
        Serial.println("Error while updating configuration");
    }
}

void loop() {
    // Your loop code (if needed)
}
