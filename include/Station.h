/**
 * @file Station.h
 * @brief Contains the declaration of the Station class.
 *
 * This header file declares the Station class, which represents a station in the project.
 * Each station has an ID and a code.
 */

#ifndef PROJ_DA_01_STATION_H
#define PROJ_DA_01_STATION_H

#include "Code.h"

/**
 * @class Station
 * @brief Represents a water pumping station.
 *
 * Each station has an ID and a code.
 */
class Station {
public:
    /**
     * @brief Default constructor for the Station class.
     */
    Station();

    /**
     * @brief Constructs a Station object with the given parameters.
     * @param id The ID of the station.
     * @param code The code of the station.
     */
    Station(int id, Code code);

    /**
     * @brief Gets the ID of the station.
     * @return The ID of the station.
     */
    int getId() const;

    /**
     * @brief Sets the ID of the station.
     * @param id The ID of the station.
     */
    void setId(const int& id);


    /**
     * @brief Gets the code of the station.
     * @return The code of the station.
     */
    Code getCode() const;

    /**
     * @brief Sets the code of the station.
     * @param code The code of the station.
     */
    void setCode(const Code& code);
private:
    int id;     ///< The ID of the station.
    Code code;  ///< The code of the station.
};

#endif //PROJ_DA_01_STATION_H
