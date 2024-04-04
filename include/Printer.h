#ifndef FEUP_DA_01_PRINTER_H
#define FEUP_DA_01_PRINTER_H

#include "ParseData.h"

void exportReservoirData(const std::string& filename, const DataContainer& dataContainer);
void exportStationData(const std::string& filename, const DataContainer& dataContainer);
void exportCityData(const std::string& filename, const DataContainer& dataContainer);
static void printHeader();
void printCityMaxFlow(const std::string& name, const std::string& code, const double& maxFlow);
void printEachCityMaxFlow(const Graph<Code>& bsmGraph, const DataContainer& dataContainer);
void printSpecificCityMaxFlow(const Graph<Code>& bsmGraph, const DataContainer& dataContainer, const Code& city);
void printCitiesWithWaterFlowDeficit(const Graph<Code>& bsmGraph, const DataContainer& dataContainer);
void printEachPipeInitialMetrics(const Graph<Code>& bsmGraph);

#endif //FEUP_DA_01_PRINTER_H
