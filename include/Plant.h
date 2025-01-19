#include <string>
#include <vector>
#include "DeviceDriver.h"

#ifndef PLANT_H
#define PLANT_H


class Plant
{
    public:
        Plant();
        virtual ~Plant();

    protected:
        std::string name;
        std::vector<DeviceDriver> drivers;

    private:

};

#endif // PLANT_H
