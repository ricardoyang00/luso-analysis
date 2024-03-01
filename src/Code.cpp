#include "Code.h"

Code::Code() {}

Code::Code(const std::string& code) {
    std::string delimiter = "_";
    size_t pos = code.find(delimiter);

    if (pos != std::string::npos) {
        std::string typeStr = code.substr(0, pos);
        if (typeStr == "R") {
            type = CodeType::RESERVOIR;
        } else if (typeStr == "PS") {
            type = CodeType::STATION;
        } else if (typeStr == "C") {
            type = CodeType::CITY;
        } else {
            std::cerr << "Invalid code type: " << typeStr << std::endl;
            type = CodeType::CITY; // Set a default type or handle error accordingly
        }
        number = std::stoi(code.substr(pos + delimiter.length()));
    } else {
        std::cerr << "Invalid code format: " << code << std::endl;
        // Set default values or handle error accordingly
        type = CodeType::CITY;
        number = 0;
    }
}

CodeType Code::getType() const {
    return type;
}

int Code::getNumber() const {
    return number;
}

std::string Code::getCode() const {
    return code;
}