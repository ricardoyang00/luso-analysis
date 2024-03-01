#include "City.h"

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