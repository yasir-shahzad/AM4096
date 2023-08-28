# AM4096 Encoder Arduino Library

![AM4096 Encoder](images/am4096.jpg)

## Description

The AM4096 Encoder Arduino Library provides a convenient way to interface with the AM4096 rotary magnetic encoder chip using the I2C protocol. This library enables you to read configuration data and measurement output from the AM4096 encoder.

The AM4096 encoder is a 12-bit rotary magnetic encoder chip that offers accurate position sensing for various applications.

## Features

- Read configuration data from the AM4096 encoder.
- Update configuration settings, including EEPROM updates.
- Read measurement output data.
- Find and initialize the encoder device.
- Software-based I2C communication.

## Installation

1. Download the latest release of the library from [GitHub](https://github.com/yasir-shahzad/AM4096/releases).
2. Extract the downloaded ZIP file.
3. Move the extracted folder to the Arduino libraries directory.
   - For Windows: `Documents/Arduino/libraries`
   - For macOS: `~/Documents/Arduino/libraries`

## Usage

1. Include the library in your Arduino sketch:

```cpp
#include <AM4096.h>

## Documentation
For more details on available methods and usage, refer to the library documentation.

## Contributing
Contributions are welcome! If you find a bug or want to improve the library, please open an issue or submit a pull request.

## License
This library is licensed under the MIT License. See the LICENSE file for more details.
