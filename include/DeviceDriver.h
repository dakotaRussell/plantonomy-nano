#include <iostream>

#ifndef DEVICEDRIVER_H
#define DEVICEDRIVER_H

class DeviceDriver
{
    public:
        DeviceDriver();
        virtual ~DeviceDriver();
        virtual void open(const unsigned char *configOptions, size_t len) = 0;
        virtual double read();
        virtual ssize_t write(const unsigned char *buf, size_t len);
    protected:
        ssize_t buf_size = 0;
        const char* deviceAddr;
};

#endif // DEVICEDRIVER_H
