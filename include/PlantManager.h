#ifndef PLANTMANAGER_H
#define PLANTMANAGER_H
#include <vector>
#include "Plant.h"

class PlantManager
{
    public:
        PlantManager();
        virtual ~PlantManager();
    protected:

    private:
        std::vector<Plant> plants;
        void initializePlants();
};

#endif // PLANTMANAGER_H
