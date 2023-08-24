/**
 * @file GetConfiguration.ino
 * @brief Example of using the AM4096 encoder to read configuration.
 */

#include <Wire.h>
#include <AM4096.h> // Include the header file

// Create an instance of the AM4096 encoder class with the specified address
AM4096 encoder(0x5A); // I2C bus, device address
AM4096_config_data currentConfiguration;

void setup() {
    Serial.begin(9600);
    Serial.println("Am4096 GetConfiguration Example"); 
    Wire.begin();
    // Initialize communication with the encoder
    encoder.init();

    // Get the current configuration from the encoder
    encoder.getConfiguration(&currentConfiguration);

    // Print the configuration
    // Serial.println("Current Configuration:");
    encoder.printAM4096Configuration(&currentConfiguration);
}

void loop() {
  // Your loop code (if needed)
}
