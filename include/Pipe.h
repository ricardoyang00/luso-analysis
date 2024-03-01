#ifndef PROJ_DA_01_PIPE_H
#define PROJ_DA_01_PIPE_H

#include "Code.h"

class Pipe {
public:
    Pipe(Code sourceCode, Code targetCode, int capacity, bool direction);
    Code getSourceCode() const;
    Code getTargetCode() const;
    int getCapacity() const;
    bool getDirection() const;

private:
    Code sourceCode;
    Code targetCode;
    int capacity;
    bool direction;         //undirected - 1 , bidirectional - 0
};

Pipe::Pipe(Code sourceCode, Code targetCode, int capacity, bool direction)
        : sourceCode(sourceCode), targetCode(targetCode), capacity(capacity), direction(direction) {}

Code Pipe::getSourceCode() const {
    return sourceCode;
}

Code Pipe::getTargetCode() const {
    return targetCode;
}

int Pipe::getCapacity() const {
    return capacity;
}

bool Pipe::getDirection() const {
    return direction;
}

#endif //PROJ_DA_01_PIPE_H
