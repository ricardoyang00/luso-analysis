#ifndef FEUP_DA_01_MENU_H
#define FEUP_DA_01_MENU_H

#include <vector>
#include <iostream>
#include "BasicServiceMetrics.h"
#include "Printer.h"

class Menu {
private:
    std::vector<std::string> menuIndex;
    void printMenu();

public:
    Menu();
    int run();
};


#endif //FEUP_DA_01_MENU_H
