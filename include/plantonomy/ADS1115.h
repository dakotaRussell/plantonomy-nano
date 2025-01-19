#ifndef ADS1115_H
#define ADS1115_H

#include <cstring>
#include <cstdint>
#include <iostream>
#include "DeviceDriver.h"

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
        uint16_t readDigitalValue();
};

#endif // ADS1115_H
