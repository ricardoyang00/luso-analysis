#ifndef PROJ_DA_01_CITY_H
#define PROJ_DA_01_CITY_H

#include "Code.h"
#include <string>

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

City::City(std::string name, int id, Code code, int demand, int population)
        : name(name), id(id), code(code), demand(demand), population(population) {}

const std::string City::getName() const {
    return name;
}

int City::getId() const {
    return id;
}

Code City::getCode() const {
    return code;
}

int City::getDemand() const {
    return demand;
}

int City::getPopulation() const {
    return population;
}

#endif //PROJ_DA_01_CITY_H
