#include "Device.h"

Device::Device(){
    DeviceConfig def;
    config = &def;

    CommConfig commConfig;
    config->commConfig = &commConfig;

    comm = new CommunicationProtocol(config->commConfig); 
}

Device::Device(DeviceConfig* deviceConfig){
    if (deviceConfig == nullptr) return;
    
    config = deviceConfig;
    comm = new CommunicationProtocol(config->commConfig);
}

Device::~Device(){
    delete(comm);
}
