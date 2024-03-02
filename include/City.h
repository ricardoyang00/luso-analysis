#ifndef PROJ_DA_01_CITY_H
#define PROJ_DA_01_CITY_H

#include "Code.h"

class City {
public:
    City();
    City(std::string name, int id, Code code, int demand, int population);
    const std::string getName() const;
    void setName(const std::string& name);
    int getId() const;
    void setId(const int& id);
    Code getCode() const;
    void setCode(const Code& code);
    double getDemand() const;
    void setDemand(const double& demand);
    int getPopulation() const;
    void setPopulation(const int& population);
private:
    std::string name;
    int id;
    Code code;
    int demand;
    int population;
};

#endif //PROJ_DA_01_CITY_H
