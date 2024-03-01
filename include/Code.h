#ifndef PROJ_DA_01_CODE_H
#define PROJ_DA_01_CODE_H

#include <string>
#include <iostream>

enum class CodeType { RESERVOIR, STATION, CITY };

class Code {
public:
    Code();
    Code(const std::string& code);
    std::string getCode() const;
    CodeType getType() const;
    int getNumber() const;

private:
    std::string code;
    CodeType type;
    int number;
};

#endif //PROJ_DA_01_CODE_H