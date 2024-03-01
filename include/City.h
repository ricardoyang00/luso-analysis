#ifndef PROJ_DA_01_CITY_H
#define PROJ_DA_01_CITY_H

#include "Code.h"

class City {
public:
    City(std::string name, int id, Code code, int demand, int population);
    const std::string getName() const;
    int getId() const;
    Code getCode() const;
    int getDemand() const;
    int getPopulation() const;
private:
    std::string name;
    int id;
    Code code;
    int demand;
    int population;
};

#endif //PROJ_DA_01_CITY_H
