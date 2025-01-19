

#ifndef I2CCOMM_H
#define I2CCOMM_H

#include "Connection.h"
#include "i2c.h"
#include <cstdint>
#include <iostream>
#include <cstring>

#define DEFAULT_I2C_ADDR 0x48
#define CONVERSION_REG_ADDR 0x00
#define CONFIG_REG_ADDR 0x01


class I2CComm : public Connection
{
    public:
        I2CComm();
        virtual ~I2CComm();
        void open(const unsigned char *configOptions, size_t len);
        virtual double read();
        virtual ssize_t write(const unsigned char *buf, size_t len);

    protected:
        ssize_t buf_size = 0;

    private:
        unsigned char buf[256];
        I2CDevice device;
        I2C_READ_HANDLE i2cReadHandle;
        I2C_WRITE_HANDLE i2cWriteHandle;
        uint16_t readDigitalValue();
};

#endif // I2CCOMM_H
