/**
 * @file GetConfiguration.ino
 * @brief Example of using the AM4096 encoder to read configuration.
 */
#include <Wire.h>
#include <AM4096.h>

// Constants for configuration settings
const uint16_t DEVICE_ADDRESS = 0x5A;

// Create an instance of the AM4096 encoder class
AM4096 encoder(DEVICE_ADDRESS); // I2C bus, device address

// Creating a configuration data instance for AM4096
AM4096_config_data config;

void setup()
{
    Serial.begin(9600);
    while(!Serial){
      ;
    }
    Serial.println(F("Am4096 SetConfiguration Example"));
    Wire.begin();
    // Initialize the communication with the encoder
    encoder.init();

    config.fields.Reg35   = 0x01; // Set Regulator voltage bit
    config.fields.Slowint = 0x01; // Set Interpolator delay bit
    config.fields.Abridis = 0x01; // Set Enabling A B Ri outputs bit
    config.fields.Res     = 0x04; // Set Interpolation factor rate
    config.fields.Sth     = 0x07; // Set Tacho measuring range
    config.fields.SSIcfg  = 0x03; // Set SSI settings
    config.fields.Dac     = 0x03; // Set Linear voltage period selection
    config.fields.Dact    = 0x01; // Set Select the output on Vout/Tout pin bit

    // Update the configuration
    int configurationUpdated = encoder.updateConfiguration(&config, true);
    if (!configurationUpdated) {
        Serial.println(F("Configuration updated"));
    } else {
        Serial.println(F("Error while updating configuration"));
    }
}

void loop() {
    // Your loop code (if needed)
}
