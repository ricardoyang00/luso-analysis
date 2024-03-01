#ifndef PROJ_DA_01_RESERVOIR_H
#define PROJ_DA_01_RESERVOIR_H

#include "Code.h"

class Reservoir {
public:
    Reservoir();
    Reservoir(std::string name, std::string municipality, int id, Code code, int maxDelivery);
    const std::string getName() const;
    void setName(const std::string& name);
    const std::string getMunicipality() const;
    void setMunicipality(const std::string& municipality);
    int getId() const;
    void setId(const int& id);
    Code getCode() const;
    void setCode(const Code& code);
    int getMaxDelivery() const;
    void setMaxDelivery(const int& maxDelivery);
private:
    std::string name;
    std::string municipality;
    int id;
    Code code;
    int maxDelivery;
};

Reservoir::Reservoir() {}

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

void Reservoir::setName(const std::string &name) {
    this->name = name;
}

void Reservoir::setMunicipality(const std::string &municipality) {
    this->municipality = municipality;
}

void Reservoir::setId(const int &id) {
    this->id = id;
}

void Reservoir::setCode(const Code &code) {
    this->code = code;
}

void Reservoir::setMaxDelivery(const int &maxDelivery) {
    this->maxDelivery = maxDelivery;
}

#endif //PROJ_DA_01_RESERVOIR_H
