#ifndef FEUP_DA_01_MENU_H
#define FEUP_DA_01_MENU_H

#include <vector>
#include <iostream>
#include "BasicServiceMetrics.h"
#include "Printer.h"

class Menu {
private:
    ParseData parser;
    std::vector<std::string> menuIndex;
    BasicServiceMetrics bsm;

    void printMenu();
    static void clearScreen();
    static void waitPress();
    int inputParser(int& choice, std::string text);

    void printAllDataContainer();
    int printSpecificDataContainer();
    void getTotalMaxFlow();
    void getCityFlow();

public:
    Menu();
    int run();
};


#endif //FEUP_DA_01_MENU_H
