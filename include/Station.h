#ifndef PROJ_DA_01_STATION_H
#define PROJ_DA_01_STATION_H

#include <string>

class Station {
public:
    Station();
    Station(int id, std::string code);
    int getId();
    std::string getCode();
private:
    int id;
    std::string code;
};

#endif //PROJ_DA_01_STATION_H
