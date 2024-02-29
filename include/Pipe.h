#ifndef PROJ_DA_01_PIPE_H
#define PROJ_DA_01_PIPE_H

#include <string>

class Pipe {
public:
    Pipe();
    Pipe(std::string sourceCode, std::string targetCode, int capacity, bool direction);
    std::string getSourceCode();
    std::string getTargetCode();
    int getCapacity();
    bool getDirection();

private:
    std::string sourceCode;
    std::string targetCode;
    int capacity;
    bool direction;         //undirected - 1 , bidirectional - 0
};

#endif //PROJ_DA_01_PIPE_H
