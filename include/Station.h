#ifndef PROJ_DA_01_STATION_H
#define PROJ_DA_01_STATION_H

#include "Code.h"

class Station {
public:
    Station(int id, Code code);
    int getId() const;
    Code getCode() const;
private:
    int id;
    Code code;
};

#endif //PROJ_DA_01_STATION_H
