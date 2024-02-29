#ifndef PROJ_DA_01_CITY_H
#define PROJ_DA_01_CITY_H

#include "Code.h"
#include <string>

class City {
public:
    City();
    City(std::string name, int id, Code code, int demand, int population);
    std::string getName();
    int getId();
    Code getCode();
    int getDemand();
    int getPopulation();
private:
    std::string name;
    int id;
    Code code;
    int demand;
    int population;
};

#endif //PROJ_DA_01_CITY_H
