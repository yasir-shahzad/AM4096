/**
 * @file SetDeviceID.ino
 * @brief Example of using the AM4096 encoder to change it id.
 */
#include <Wire.h>
#include <AM4096.h>

// Constants for configuration settings
const uint16_t DEVICE_ADDRESS = 0x5A;

// Create an instance of the AM4096 encoder class
AM4096 encoder(DEVICE_ADDRESS); // I2C bus, device address

void setup()
{
    Serial.begin(9600);
    while(!Serial){
      ;
    }
    Serial.println(F("Am4096 SetHwAdress Example"));
    Wire.begin();
    // Initialize the communication with the encoder
    if(encoder.init() == 1)
    {
      Serial.println("Device id not correct");
      while(1);
    } esle {
      Serial.println("Device id correct");
    }

   if( encoder.setNewHwAddr(0x5B))  // new deivice id
     Serial.println("cant set new id");
}

void loop() {
    // Your loop code (if needed)
}
