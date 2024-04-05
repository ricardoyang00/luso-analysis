#ifndef FEUP_DA_01_PRINTER_H
#define FEUP_DA_01_PRINTER_H

#include "ParseData.h"
#include <cmath>

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
 * @brief Print a header for city maximum flow data.
 */
static void printHeader();

/**
 * @brief Print maximum flow data for the city.
 *
 * @param name The name of the city.
 * @param code The code of the city.
 * @param maxFlow The maximum flow for the city.
 */
void printCityMaxFlow(const std::string& name, const std::string& code, const double& maxFlow);

/**
 * @brief Print maximum flow data for each city in the water distribution system.
 *
 * @param bsmGraph The graph after running Edmonds-Karp's algorithm.
 * @param dataContainer The container holding the graph data.
 */
void printEachCityMaxFlow(const Graph<Code>& bsmGraph, const DataContainer& dataContainer);

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

#endif //FEUP_DA_01_PRINTER_H
