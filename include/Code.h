#ifndef PROJ_DA_01_CODE_H
#define PROJ_DA_01_CODE_H

#include <string>
#include <iostream>

enum class CodeType { RESERVOIR, STATION, CITY };

class Code {
public:
    Code();
    Code(const std::string& code);
    std::string getCompleteCode() const;
    CodeType getType() const;
    int getNumber() const;
    std::string codeTypeToString() const;
    bool operator==(const Code& other) const;

private:
    std::string completeCode;
    CodeType type;
    int number;
};

#endif //PROJ_DA_01_CODE_H