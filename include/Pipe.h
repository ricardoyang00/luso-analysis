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



#endif //PROJ_DA_01_PIPE_H
