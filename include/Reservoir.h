#ifndef PROJ_DA_01_RESERVOIR_H
#define PROJ_DA_01_RESERVOIR_H

#include "Code.h"
#include <string>

class Reservoir {
public:
    Reservoir();
    Reservoir(std::string name, std::string municipality, int id, Code code, int maxDelivery);
    std::string getName();
    std::string getMunicipality();
    int getId();
    Code getCode();
    int getMaxDelivery();
private:
    std::string name;
    std::string municipality;
    int id;
    Code code;
    int maxDelivery;
};

#endif //PROJ_DA_01_RESERVOIR_H
