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

#endif //PROJ_DA_01_RESERVOIR_H
