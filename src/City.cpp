#include "City.h"

using namespace std;

City::City() {}

City::City(string name, int id, Code code, int demand, int population)
        : name(name), id(id), code(code), demand(demand), population(population) {}

const string City::getName() const {
    return name;
}

void City::setName(const string &name) {
    this->name = name;
}

int City::getId() const {
    return id;
}

void City::setId(const int &id) {
    this->id = id;
}

Code City::getCode() const {
    return code;
}

void City::setCode(const Code &code) {
    this->code = code;
}

double City::getDemand() const {
    return demand;
}

void City::setDemand(const double &demand) {
    this->demand = demand;
}

int City::getPopulation() const {
    return population;
}

void City::setPopulation(const int &population) {
    this->population = population;
}
