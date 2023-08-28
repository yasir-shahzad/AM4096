/**
 * @file GetRPM.ino
 * @brief Example of using the AM4096 encoder to read RPM.
 */

#include <Wire.h>
#include <AM4096.h>

// Specify the I2C address of the AM4096 encoder
const uint8_t DEVICE_ADDRESS = 0x5A;

// Create an instance of the AM4096 encoder class with the specified address
AM4096 encoder(DEVICE_ADDRESS);

// Structure to store the encoder output data
AM4096_output_data outputData;

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        // Wait for serial port to connect (for debugging)
    }
    Serial.println(F("AM4096 GetRPM Example"));
    Wire.begin();
    // Initialize communication with the encoder
    encoder.init();
}

void loop() {
    // Read output data registers from the encoder
    int readStatus = encoder.readOutputDataRegisters(&outputData);

    // Check if the read was successful
    if (readStatus == AM4096_ERROR_NONE) {
        // Get the relative position (Rpos) field, which represents RPM
        uint16_t rpm = outputData.fields.Tho;

        // Print the RPM value
        Serial.print("RPM: ");
        Serial.println(rpm);
    }

    // Delay before the next reading
    delay(100);
}
