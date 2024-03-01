#include "Pipe.h"

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