#ifndef PROJ_DA_01_STATION_H
#define PROJ_DA_01_STATION_H

#include "Code.h"
#include <string>

class Station {
public:
    Station();
    Station(int id, Code code);
    int getId();
    Code getCode();
private:
    int id;
    Code code;
};

#endif //PROJ_DA_01_STATION_H
