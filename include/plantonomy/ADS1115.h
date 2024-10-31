#ifndef ADS1115_H
#define ADS1115_H
#include "i2c.h"
#include <cstdint>
#include <iostream>
#include <cstring>

#define DEFAULT_I2C_ADDR 0x48
#define CONVERSION_REG_ADDR 0x00
#define CONFIG_REG_ADDR 0x01

class ADS1115
{
    public:
        ADS1115();
        ADS1115(const char* deviceAddr, unsigned char configA, unsigned char configB);
        double calculateAnalogValue();
        void printI2cData(const unsigned char *data, size_t len);
        uint16_t readDigitalValue();
        virtual ~ADS1115();

    protected:
        I2CDevice device;
        I2C_READ_HANDLE i2cReadHandle;
        I2C_WRITE_HANDLE i2cWriteHandle;

    private:
        unsigned char buf[256];
        size_t buf_size;
};

#endif // ADS1115_H
