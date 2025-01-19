#ifndef DEVICEDRIVER_H
#define DEVICEDRIVER_H

#include <iostream>
#include "Connection.h"

class DeviceDriver
{
    public:
        DeviceDriver();
        DeviceDriver(const char* deviceAddr);
        virtual ~DeviceDriver();
        virtual void open(const unsigned char *configOptions, size_t len) = 0;
        virtual double read();
        virtual ssize_t write(const unsigned char *buf, size_t len);
    protected:
        ssize_t buf_size = 0;
        const char* deviceAddr;
        Connection connection;
};

#endif // DEVICEDRIVER_H
