#include "Station.h"

Station::Station() {}

Station::Station(int id, Code code) : id(id), code(code) {}

int Station::getId() const {
    return id;
}

void Station::setId(const int &id) {
    this->id = id;
}

Code Station::getCode() const {
    return code;
}

void Station::setCode(const Code &code) {
    this->code = code;
}
