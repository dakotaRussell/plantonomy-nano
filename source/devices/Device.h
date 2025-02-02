#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include "CommunicationProtocol.h"

struct DeviceConfig{
    std::string name = "UnnamedDevice";
    std::string address = "/dev/i2c-0/";
    CommConfig* commConfig = nullptr;
};

class Device {
    public:
	Device();
	Device(DeviceConfig* deviceConfig);
        ~Device();

    protected:
	DeviceConfig* config;
	CommunicationProtocol* comm;
};

#endif // DEVICE_H
