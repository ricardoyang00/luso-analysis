#ifndef PROJ_DA_01_STATION_H
#define PROJ_DA_01_STATION_H

#include "Code.h"

class Station {
public:
    Station();
    Station(int id, Code code);
    int getId() const;
    void setId(const int& id);
    Code getCode() const;
    void setCode(const Code& code);
private:
    int id;
    Code code;
};

#endif //PROJ_DA_01_STATION_H
