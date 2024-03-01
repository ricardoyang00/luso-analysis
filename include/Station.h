#ifndef PROJ_DA_01_STATION_H
#define PROJ_DA_01_STATION_H

#include "Code.h"
#include <string>

class Station {
public:
    Station(int id, Code code);
    int getId() const;
    Code getCode() const;
private:
    int id;
    Code code;
};

Station::Station(int id, Code code) : id(id), code(code) {}

int Station::getId() const {
    return id;
}

Code Station::getCode() const {
    return code;
}

#endif //PROJ_DA_01_STATION_H
