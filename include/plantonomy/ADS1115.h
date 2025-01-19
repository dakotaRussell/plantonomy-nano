#ifndef ADS1115_H
#define ADS1115_H
#include "i2c.h"
#include <cstdint>
#include <iostream>
#include <cstring>
#include "DeviceDriver.h"

#define DEFAULT_I2C_ADDR 0x48
#define CONVERSION_REG_ADDR 0x00
#define CONFIG_REG_ADDR 0x01

class ADS1115 : public DeviceDriver
{
    public:
        ADS1115();
        ADS1115(const char* deviceAddr, unsigned char configA, unsigned char configB);
        virtual ~ADS1115();

        void open(const unsigned char *configOptions, size_t len);
        double read();
        ssize_t write(const unsigned char *buf, size_t len);
        void printI2cData(const unsigned char *data, size_t len);

    private:
        unsigned char buf[256];
        I2CDevice device;
        I2C_READ_HANDLE i2cReadHandle;
        I2C_WRITE_HANDLE i2cWriteHandle;

        uint16_t readDigitalValue();
};

#endif // ADS1115_H
