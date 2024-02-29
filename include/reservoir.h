#ifndef PROJ_DA_01_RESERVOIR_H
#define PROJ_DA_01_RESERVOIR_H

#include <string>

class Reservoir {
public:
    Reservoir();
    Reservoir(std::string name, std::string municipality, int id, std::string code, int maxDelivery);
    std::string getName();
    std::string getMunicipality();
    int getId();
    std::string getCode();
    int getMaxDelivery();
private:
    std::string name;
    std::string municipality;
    int id;
    std::string code;
    int maxDelivery;
};

#endif //PROJ_DA_01_RESERVOIR_H
