#ifndef PROJ_DA_01_CODE_H
#define PROJ_DA_01_CODE_H

#include <string>

enum class CodeType { RESERVOIR, STATION, CITY };

class Code {
public:
    Code(const std::string& code);
private:
    CodeType type;
    int number;
};

Code::Code(const std::string& code) {
    std::string delimiter = "_";
    size_t pos = code.find(delimiter);

    if (pos != std::string::npos) {
        std::string typeStr = code.substr(0, pos);
        if (typeStr == "WR") {
            type = CodeType::RESERVOIR;
        } else if (typeStr == "PS") {
            type = CodeType::STATION;
        } else if (typeStr == "C") {
            type = CodeType::CITY;
        }
        number = std::stoi(code.substr(pos + delimiter.length()));
    }
}

#endif //PROJ_DA_01_CODE_H