/**
 * @file Menu.h
 * @brief Contains the declaration of the Menu class.
 *
 * This header file declares the Menu class, which provides functionality for displaying and interacting with a menu
 * for managing data related to reservoirs, pumping stations, and cities in a water distribution system.
 */

#ifndef FEUP_DA_01_MENU_H
#define FEUP_DA_01_MENU_H

#include "BasicServiceMetrics.h"
#include "Printer.h"

/**
 * @class Menu
 * @brief Class representing a menu for managing data related to a water distribution system.
 *
 * The Menu class provides functionality for displaying and interacting with a menu
 * for managing data related to reservoirs, pumping stations, and cities in a water distribution system.
 */
class Menu {
private:
    ParseData parser;                   /**< ParseData object for handling data parsing. */
    BasicServiceMetrics bsm;            /**< BasicServiceMetrics object for calculating basic service metrics. */
    std::vector<std::string> menuIndex; /**< Vector storing menu options. */

    /**
     * @brief Prints the menu options to the console.
     */
    void printMenu();

    /**
     * @brief Clears the console screen.
     */
    static void clearScreen();

    /**
     * @brief Pauses execution and waits for user input.
     */
    static void waitPress();

    /**
     * @brief Parses user input.
     * @param choice Reference to store the user's choice.
     * @param text Text prompt for input.
     * @return Integer representing the success of input parsing.
     */
    static int inputParser(int& choice, const std::string& text);

    /**
     * @brief Prints data of all reservoirs, pumping stations, and cities.
     */
    void printAllDataContainer();

    /**
     * @brief Calculates and prints the total maximum flow in the system.
     */
    void getTotalMaxFlow();

    /**
     * @brief Prints the user selected city max flow
     */
    void printSpecificCityFlow();

    /**
     * @brief Prints affected cities given old and new cities' flow.
     * @param oldCitiesFlow Map containing old cities' flow.
     * @param newCitiesFlow Map containing new cities' flow.
     */
    void printAffectedCities(std::map<int,double> oldCitiesFlow, std::map<int,double> newCitiesFlow);

    /**
     * @brief Removes a reservoir from the system.
     */
    void removeReservoir();

    /**
     * @brief Removes a pumping station from the system.
     */
    void removePumpingStation();

    /**
     * @brief Removes pipes from the system.
     */
    void removePipes();

    /**
     * @brief For each city, determine which pipelines, if ruptured would make it impossible
     * to deliver the desired amount of water to a given city.
     */
    void criticalPipes();

public:
    /**
     * @brief Default constructor for the Menu class.
     */
    Menu();

    /**
     * @brief Runs the menu interface.
     * @return Integer representing the success of menu execution.
     */
    int run();
};


#endif //FEUP_DA_01_MENU_H
