#include <iostream>

#include "CommunicationProtocol.h"
#include "Device.h"

int main(){
    // Insert some kind of data input -> class creation logic.
    CommConfig commConfig{"bus0", "0x49"};
    DeviceConfig devConfig{"ADC","virtual", &commConfig};
    Device adc(&devConfig);

    std::cout << "Hello World!" << std::endl;
    return 0;
}
