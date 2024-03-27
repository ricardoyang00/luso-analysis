#ifndef FEUP_DA_01_PRINTER_H
#define FEUP_DA_01_PRINTER_H

#include "ParseData.h"

void printHashInfo(const DataContainer& dataContainer, const Code& code);
void printAllHashInfo(const DataContainer& dataContainer);
static void printHeader();
void printCityMaxFlow(const std::string& name, const std::string& code, const double& maxFlow);
void printEachCityMaxFlow(const Graph<Code>& bsmGraph, const DataContainer& dataContainer);
void printSpecificCityMaxFlow(const Graph<Code>& bsmGraph, const DataContainer& dataContainer, const Code& city);

#endif //FEUP_DA_01_PRINTER_H
