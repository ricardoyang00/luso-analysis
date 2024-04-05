/**
 * @file City.h
 * @brief Contains the declaration of the City class.
 *
 * This header file declares the City class, which represents a Portuguese city.
 * Each city has a name, an ID, a code, a demand, and a population.
 */

#ifndef PROJ_DA_01_CITY_H
#define PROJ_DA_01_CITY_H

#include "Code.h"

/**
 * @class City
 * @brief Represents a Portuguese city.
 *
 * Each city has a name, an ID, a code, a demand, and a population.
 */
class City {
public:
    /**
     * @brief Default constructor for the City class.
     */
    City();

    /**
     * @brief Constructs a City object with the given parameters.
     * @param name The name of the city.
     * @param id The ID of the city.
     * @param code The code of the city.
     * @param demand The demand of the city.
     * @param population The population of the city.
     */
    City(std::string name, int id, Code code, int demand, int population);

    /**
     * @brief Gets the name of the city.
     * @return The name of the city.
     */
    const std::string getName() const;

    /**
     * @brief Sets the name of the city.
     * @param name The name of the city.
     */
    void setName(const std::string& name);

    /**
     * @brief Gets the ID of the city.
     * @return The ID of the city.
     */
    int getId() const;

    /**
     * @brief Sets the ID of the city.
     * @param id The ID of the city.
     */
    void setId(const int& id);

    /**
     * @brief Gets the code of the city.
     * @return The code of the city.
     */
    Code getCode() const;

    /**
     * @brief Sets the code of the city.
     * @param code The code of the city.
     */
    void setCode(const Code& code);

    /**
     * @brief Gets the demand of the city.
     * @return The demand of the city.
     */
    double getDemand() const;

    /**
     * @brief Sets the demand of the city.
     * @param demand The demand of the city.
     */
    void setDemand(const double& demand);

    /**
     * @brief Gets the population of the city.
     * @return The population of the city.
     */
    int getPopulation() const;

    /**
     * @brief Sets the population of the city.
     * @param population The population of the city.
     */
    void setPopulation(const int& population);
private:
    std::string name;   ///< The name of the city.
    int id;             ///< The ID of the city.
    Code code;          ///< The code of the city.
    int demand;         ///< The water demand of the city in m^3/sec.
    int population;     ///< The population of the city.
};

#endif //PROJ_DA_01_CITY_H
