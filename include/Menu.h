#ifndef FEUP_DA_01_MENU_H
#define FEUP_DA_01_MENU_H

#include "BasicServiceMetrics.h"
#include "Printer.h"
#include <vector>
#include <iostream>

class Menu {
private:
    ParseData parser;
    std::vector<std::string> menuIndex;
    BasicServiceMetrics bsm;

    void printMenu();
    static void clearScreen();
    static void waitPress();
    static int inputParser(int& choice, const std::string& text);

    void printAllDataContainer();
    void getTotalMaxFlow();

    void printAffectedCities(std::map<int,double> oldCitiesFlow, std::map<int,double> newCitiesFlow);
    void removeReservoir();
    void removePumpingStation();

public:
    Menu();
    int run();
};


#endif //FEUP_DA_01_MENU_H
