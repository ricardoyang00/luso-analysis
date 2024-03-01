#ifndef PROJ_DA_01_RESERVOIR_H
#define PROJ_DA_01_RESERVOIR_H

#include "Code.h"
#include <string>

class Reservoir {
public:
    Reservoir(std::string name, std::string municipality, int id, Code code, int maxDelivery);
    const std::string getName() const;
    const std::string getMunicipality() const;
    int getId() const;
    Code getCode() const;
    int getMaxDelivery() const;
private:
    std::string name;
    std::string municipality;
    int id;
    Code code;
    int maxDelivery;
};

Reservoir::Reservoir(std::string name, std::string municipality, int id, Code code, int maxDelivery) :
    name(name), municipality(municipality), id(id), code(code), maxDelivery(maxDelivery) {}

const std::string Reservoir::getName() const {
    return name;
}

const std::string Reservoir::getMunicipality() const {
    return municipality;
}

int Reservoir::getId() const {
    return id;
}

Code Reservoir::getCode() const {
    return code;
}

int Reservoir::getMaxDelivery() const {
    return maxDelivery;
}

#endif //PROJ_DA_01_RESERVOIR_H
