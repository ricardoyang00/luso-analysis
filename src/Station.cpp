#include "Station.h"

Station::Station(int id, Code code) : id(id), code(code) {}

int Station::getId() const {
    return id;
}

Code Station::getCode() const {
    return code;
}