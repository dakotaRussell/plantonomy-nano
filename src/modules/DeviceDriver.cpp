#include "DeviceDriver.h"

DeviceDriver::DeviceDriver()
{
    //ctor
}

DeviceDriver::DeviceDriver(const char* deviceAddr)
{
    deviceAddr = deviceAddr;
}

DeviceDriver::~DeviceDriver()
{
    //dtor
}

double DeviceDriver::read()
{
    // unused
    return 0;
}

ssize_t DeviceDriver::write(const unsigned char *buf, size_t len)
{
    // unused
    return 0;
}

void DeviceDriver::open(const unsigned char *configOptions, size_t len)
{
    connection.open(configOptions, len);
}
