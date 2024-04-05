/**
 * @file printer.h
 * @brief Contains functions for exporting and printing data related to a water distribution system.
 *
 * This file defines functions for exporting reservoir, station, and city data to text files,
 * as well as functions for printing various metrics related to the water distribution system.
 *
 * The functions provided here facilitate the analysis and visualization of data associated with
 * the water distribution system, aiding in understanding its performance and characteristics.
 */

#ifndef FEUP_DA_01_PRINTER_H
#define FEUP_DA_01_PRINTER_H

#include "ParseData.h"
#include <cmath>
#include <map>

/**
 * @brief Export reservoir data to a text file.
 *
 * @param filename The name of the file to export data to.
 * @param dataContainer The container holding the graph data.
 */
void exportReservoirData(const std::string& filename, const DataContainer& dataContainer);

/**
 * @brief Export station data to a text file.
 *
 * @param filename The name of the file to export data to.
 * @param dataContainer The container holding the graph data.
 */
void exportStationData(const std::string& filename, const DataContainer& dataContainer);

/**
 * @brief Export city data to a text file.
 *
 * @param filename The name of the file to export data to.
 * @param dataContainer The container holding the graph data.
 */
void exportCityData(const std::string& filename, const DataContainer& dataContainer);

/**
 * @brief Export maximum flow data for each city in the water distribution system to a text file.
 *
 * @param filename The name of the file to export the data to.
 * @param bsmGraph The graph after running Edmonds-Karp's algorithm.
 * @param dataContainer The container holding the graph data.
 */
void exportAllCitiesMaxFlow(const std::string& filename, const Graph<Code>& bsmGraph, const DataContainer& dataContainer);

/**
 * @brief Print a header for city maximum flow data.
 *
 * @param output The output stream where the city data will be printed.
 */
static void printHeader(std::ostream& output);

/**
 * @brief Print maximum flow data for the city.
 *
 * @param output The output stream where the city data will be printed.
 * @param name The name of the city.
 * @param code The code of the city.
 * @param maxFlow The maximum flow for the city.
 */
void printCityMaxFlow(std::ostream& output, const std::string& name, const std::string& code, const double& maxFlow);

/**
 * @brief Print maximum flow data for each city in the water distribution system.
 *
 * @param output The output stream where the city data will be printed.
 * @param bsmGraph The graph after running Edmonds-Karp's algorithm.
 * @param dataContainer The container holding the graph data.
 */
void printEachCityMaxFlow(std::ostream& output, const Graph<Code>& bsmGraph, const DataContainer& dataContainer);

/**
 * @brief Print maximum flow data for a specific city.
 *
 * @param bsmGraph The graph after running Edmond's Karp's algorithm.
 * @param dataContainer The container holding the graph data.
 * @param city The code of the specific city.
 */
void printSpecificCityMaxFlow(const Graph<Code>& bsmGraph, const DataContainer& dataContainer, const Code& city);

/**
 * @brief Print cities with water flow deficit.
 *
 * @param bsmGraph The graph after running Edmond's Karp's algorithm.
 * @param dataContainer The container holding the graph data.
 */
void printCitiesWithWaterFlowDeficit(const Graph<Code>& bsmGraph, const DataContainer& dataContainer);

/**
 * @brief Print initial metrics for each pipe in the water distribution system.
 *
 * @param bsmGraph The graph after running Edmond's Karp's algorithm.
 */
void printEachPipeInitialMetrics(const Graph<Code>& bsmGraph);

/**
 * @brief Export critical pipes for each city in the water distribution system to a text file.
 *
 * @param pathName The name of the file to export the data to.
 * @param criticalPipes The data of the critical pipes per city.
 * @param dataContainer The container holding the cities data.
 */
void exportCriticalPipesForEachCity(const std::string& pathName, const std::map<int,std::vector<std::pair<Code,Code>>>& criticalPipes, const DataContainer& dataContainer);

#endif //FEUP_DA_01_PRINTER_H
