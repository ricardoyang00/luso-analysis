#ifndef PROJ_DA_01_PIPE_H
#define PROJ_DA_01_PIPE_H

#include "Code.h"
#include <string>

class Pipe {
public:
    Pipe();
    Pipe(Code sourceCode, Code targetCode, int capacity, bool direction);
    Code getSourceCode();
    Code getTargetCode();
    int getCapacity();
    bool getDirection();

private:
    Code sourceCode;
    Code targetCode;
    int capacity;
    bool direction;         //undirected - 1 , bidirectional - 0
};

#endif //PROJ_DA_01_PIPE_H
