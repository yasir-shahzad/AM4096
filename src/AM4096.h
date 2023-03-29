/** @file AM4096.h
 * AM4096 interface library for mbed framework
 * Copyright (C)  Yasir Shahzad, 2022
 *
 * Distributed under the MIT license.
 * For full terms see the file LICENSE.md.
 */
#ifndef __AM4096_H__
#define __AM4096_H__

#include <Arduino.h>
#include <assert.h>
#include "SoftWire.h"

#define AM4096_LOGS 1

#define AM4096_MEMORY_WORD_LEN              2   ///< AM4096 memory word length in Bytes
#define AM4096_EEPROM_CONFIG_DATA_ADDR      0   ///< address of first word of AM4096 configuration in EEPROM  
#define AM4096_REGISTER_CONFIG_DATA_ADDR    48  ///< address of first word of AM4096 configuration in registers
#define AM4096_CONFIG_DATA_LEN              4   ///< AM4096 configuration length in words
#define AM4096_EEPROM_DEVICE_ID_ADDR        30  ///< addres of first word of AM4096 ID
#define AM4096_EEPROM_DEVICE_ID_LEN         2   ///< AM4960 ID length in words
#define AM4096_REGISTER_MEAS_DATA_ADDR      32  ///< address of first word of AM4096 measurement data in registers
#define AM4096_REGISTER_MEAS_DATA_LEN       4   ///< AM4096 measurement data length in words
#define AM4096_ADDR_FIRST                   0   ///< AM4096 default hw address and begining of device's address space (I2C) 
#define AM4096_ADDR_LAST                    127 ///< end of device's address space (I2C)                 
#define AM4096_ERROR_NONE                   0   ///< no error <==> success, non zero return code indicates error
#define AM4096_EEPROM_WRITE_TIME            20  ///< EEPROM write time in ms

/**
 * @brief AM4096 configuration data structure.
 *
 * More specific information about particular settings and the correct values you can
 * find in the product's datasheet: 
 * https://www.rls.si/en/fileuploader/download/download/?d=0&file=custom%2Fupload%2FAM4096D02_06_EN_data_sheet.pdf
 * or on product's webpage:
 * https://www.rls.si/en/am4096-12-bit-rotary-magnetic-encoder-chip
 * 
 * @sa AM4096_meas_fields
 */
struct AM4096_config_fields
{
    uint16_t Addr    : 7, ///< Device I2C address
                     : 1,
             Reg35   : 1, ///< Regulator voltage
             Pdie    : 1, ///< Internal power down
             Pdtr    : 2, ///< Internal power down rate
             Slowint : 1, ///< Interpolator delay
                     : 1,
             AGCdis  : 1, ///< AGC disable
             Pdint   : 1; ///< Interpolator power
    uint16_t Zin     : 12,///< Zero position data
             Sign    : 1, ///< Select the output direction
                     : 1,
             Bufsel  : 1, ///< Selects the output on pins U/Nsin, V/Psin, W/Ncos, Td/Pcos
             Abridis : 1; ///< Enabling A B Ri outputs
    uint16_t Hist    : 7, ///< Digital hysteresis value in LSB at 12bit resolution
             Daa     : 1, ///< Output position selection
             Nfil    : 8; ///< Test parameters
    uint16_t Res     : 3, ///< Interpolation factor rate
             UVW     : 3, ///< UVW number of periods/turn
             Sth     : 3, ///< Tacho measuring range
                     : 2,
             SSIcfg  : 2, ///< SSI settings
             Dac     : 2, ///< Linear voltage period selection
             Dact    : 1; ///< Select the output on Vout/Tout pin
};

/**
 * @brief AM4096 output data structure.
 *
 * More specific information about particular settings and the correct values you can
 * find in the product's datasheet: 
 * https://www.rls.si/en/fileuploader/download/download/?d=0&file=custom%2Fupload%2FAM4096D02_06_EN_data_sheet.pdf
 * or on product's webpage:
 * https://www.rls.si/en/am4096-12-bit-rotary-magnetic-encoder-chip
 * 
 * @sa AM4096_config_fields
 */
struct AM4096_meas_fields
{
    uint16_t Rpos       : 12, ///< Relative position inf.
                        : 3,  
             SRCHRpos   : 1;  ///< Relative position output valid
    uint16_t Apos       : 12, ///< Absolute position inf.
                        : 3,
             SRCHApos   : 1;  ///< Absolute position outpout valid
    uint16_t            : 13,
             Wel        : 1,  ///< Magnet too close status
             Weh        : 1,  ///< Magnet too far status
                        : 1;
    uint16_t Tho        : 10, ///< Tacho output data
             Thof       : 1,  ///< Tacho overflow info
                        : 1,
             AGCgain    : 4;  ///< AGC disable
};


/**
 * @brief Configuration data helper union.
 * @sa AM4096_config_fields 
 */
union AM4096_config_data
{
    AM4096_config_fields fields;
    uint16_t data[4];
};

/**
 * @brief Output data helper union.
 * @sa AM4096_meas_fields 
 */
union AM4096_output_data
{
    AM4096_meas_fields fields;
    uint16_t data[4];
};

/**
 * @brief AM4096 interface class.
 *
 * It allows to program AM4096 encoder and read its output and configuration registers.
 * @sa AM4096_config_data
 * @sa AM4096_output_data
 */
class AM4096  
{
    public:
        /**
         * @brief Create AM4096 interface.
         * @param i2c_instance pointer to I2C instance
         * @param hw_addr device address 
         * @return 
         */
        AM4096(SoftWire* i2c_instance, uint8_t hw_addr);

        /**
         * @brief Initialise device.
         *
         * It initialise communication with device and reads its configuration and ID. If address is incorrect it starts
         * the search procedure to find first valid device.
         * @sa findAM4096Device() 
         * @return AM4096_ERROR_NONE if success, non zero value on failure
         */
        int init();
        
        /**
         * @brief Get device ID.
         * @return device id 
         */
        uint32_t getDeviceId();
        
        /**
         * @brief Start search procedure on i2c bus.
         *
         * It starts search procedure to look for first valid device. If found, class is initialised with this address.
         * You must call init() if device was found to use it. 
         * @return AM4096_ERROR_NONE if success, non zero value on failure
         */
        int findAM4096Device();
        
        /**
         * @brief Set new device address.
         * @param hw_addr new address   
         * @return AM4096_ERROR_NONE if success, non zero value on failure
         */
        int setNewHwAddr(uint8_t hw_addr);
        
        /**
         * @brief Get current configuration.
         * @param conf_ptr pointer to configuration object to update 
         */
        void getConfiguration(AM4096_config_data * conf_ptr);
        
        /**
         * @brief Write new configuration to device.
         * @param conf_ptr pointer to configuration object 
         * @param permament if true device's EEPROM is update, otherwise only registers are udpate and configuration will be lost after power cycle
         * @return AM4096_ERROR_NONE if success, non zero value on failures  
         */
        int updateConfiguration(const AM4096_config_data * conf_ptr, bool permament=false);
        
        /**
         * @brief Read measurement data from device registers.
         * @param out_ptr pointer to output object to update
         * @return AM4096_ERROR_NONE if success, non zero value on failures   
         */
        int readOutputDataRegisters(AM4096_output_data * out_ptr);
        
        /**
         * @brief Prints formatted table with configuration registers.
         *
         * Works only if AM4096_LOGS is defined and set to 1
         * @param conf_ptr pointer to configuration to print out
         */
        static void printAM4096Configuration(const AM4096_config_data * conf_ptr);

        /**
         * @brief Prints formatted table with measurement registers.
         *
         * Works only if AM4096_LOGS is defined and set to 1
         * @param out_ptr pointer to configuration to print out
         */
        static void printAM4096OutputData(const AM4096_output_data * out_ptr);

        /**
         * @brief Write a 16bit word into AM4096 register/EEPROM.
         * @param addr register address
         * @param reg pointer to word
         * @return AM4096_ERROR_NONE if success, non zero value on failures 
         */
        int readReg(uint8_t addr, uint16_t * reg);

        /**
         * @brief Read a 16bit word from AM4096 register/EEPROM.
         * @param addr register address 
         * @param reg pointer to word
         * @return AM4096_ERROR_NONE if success, non zero value on failures 
         */
        int writeReg(uint8_t addr, uint16_t * reg); 
    
    private:
        SoftWire *_i2c;
        uint8_t _hw_addr;
        uint32_t _device_id;
        bool _initialised;
        AM4096_config_data _configuration;
};

#endif /* __AM4096_H__ */