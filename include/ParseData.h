/**
 * @file ParseData.h
 * @brief Contains the declaration of the ParseData class.
 *
 * This header file declares the ParseData class, which is responsible for parsing input data files
 * and populating the data structures used for the Water Supply Analysis and Management Tool.
 */

#ifndef PROJ_DA_01_PARSEDATA_H
#define PROJ_DA_01_PARSEDATA_H

#include "Graph.h"
#include "City.h"
#include "Reservoir.h"
#include "Station.h"
#include "Utilities.h"
#include <unordered_map>
#include <fstream>
#include <variant>

/**
 * @class DataContainer
 * @brief Represents a container for storing data entities.
 *
 * This class provides storage for reservoirs, stations, and cities using unordered maps.
 */
class DataContainer {
private:
    std::unordered_map<int, Reservoir> ReservoirHashTable;  ///< Hash table for storing reservoirs.
    std::unordered_map<int, Station> StationHashTable;      ///< Hash table for storing stations.
    std::unordered_map<int, City> CityHashTable;            ///< Hash table for storing cities.

public:
    /**
     * @brief Default constructor for the DataContainer class.
     */
    DataContainer();

    /**
     * @brief Gets the hash table of reservoirs.
     * @return The hash table of reservoirs.
     */
    std::unordered_map<int, Reservoir> getReservoirHashTable() const;

    /**
     * @brief Gets the hash table of stations.
     * @return The hash table of stations.
     */
    std::unordered_map<int, Station> getStationHashTable() const;

    /**
     * @brief Gets the hash table of cities.
     * @return The hash table of cities.
     */
    std::unordered_map<int, City> getCityHashTable() const;

    /**
     * @brief Adds a reservoir to the reservoir hash table.
     * @param code The code of the reservoir.
     * @param reservoir The reservoir to add.
     */
    void addToReservoirHashTable(Code code, Reservoir reservoir);

    /**
     * @brief Adds a pumping station to the station hash table.
     * @param code The code of the station.
     * @param station The station to add.
     */
    void addToStationHashTable(Code code, Station station);

    /**
     * @brief Adds a city to the city hash table.
     * @param code The code of the city.
     * @param city The city to add.
     */
    void addToCityHashTable(Code code, City city);
};


/**
 * @class ParseData
 * @brief Parses input data files and populates data structures.
 *
 * This class is responsible for parsing input CSV files containing data for reservoirs, stations, cities, and pipes.
 * It populates the data structures used in the project, including a graph representing connections between entities.
 */
class ParseData {
private:
    Graph<Code> codeGraph;          ///< Graph representing connections between entities.
    DataContainer dataContainer;    ///< Container for storing parsed data.
    std::string reservoirCSV;       ///< Path to the reservoirs CSV file.
    std::string stationsCSV;        ///< Path to the stations CSV file.
    std::string citiesCSV;          ///< Path to the cities CSV file.
    std::string pipesCSV;           ///< Path to the cities CSV file.

    /**
     * @brief Parses reservoir data from the reservoirs CSV file.
     */
    void parseReservoirs();

    /**
     * @brief Parses station data from the stations CSV file.
     */
    void parseStations();

    /**
     * @brief Parses city data from the cities CSV file.
     */
    void parseCities();

    /**
     * @brief Parses pipe data from the pipes CSV file.
     */
    void parsePipes();

    /**
     * @brief Creates a super source-sink graph representing connections between entities.
     */
    void makeSuperSourceSinkGraph();

public:
    /**
     * @brief Constructs a ParseData object with the given input file paths.
     * @param reservoirCSV Path to the reservoirs CSV file.
     * @param stationsCSV Path to the stations CSV file.
     * @param citiesCSV Path to the cities CSV file.
     * @param pipesCSV Path to the pipes CSV file.
     */
    ParseData(const std::string& reservoirCSV, const std::string& stationsCSV,
              const std::string& citiesCSV, const std::string& pipesCSV);

    /**
     * @brief Gets the graph representing connections between entities.
     * @return The graph representing connections between entities.
     */
    const Graph<Code>& getCodeGraph() const { return codeGraph; }


    /**
     * @brief Gets the data container storing parsed data.
     * @return The data container storing parsed data.
     */
    const DataContainer& getDataContainer() const { return dataContainer; }
};


#endif //PROJ_DA_01_PARSEDATA_H
