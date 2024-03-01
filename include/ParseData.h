#ifndef PROJ_DA_01_PARSEDATA_H
#define PROJ_DA_01_PARSEDATA_H

#include "Graph.h"
#include "Pipe.h"
#include "City.h"
#include "Reservoir.h"
#include "Station.h"
#include "Utilities.h"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <variant>

class DataContainer {
public:
    using InnerMapValue = std::variant<City, Reservoir, Station>;
    using InnerMap = std::unordered_map<int, InnerMapValue>;
    using OuterMap = std::unordered_map<CodeType, InnerMap>;

    OuterMap dataMap;
};

class ParseData {
private:
    Graph<Code> graph;
    DataContainer dataContainer;
    std::string reservoirCSV;
    std::string stationsCSV;
    std::string citiesCSV;
    std::string pipesCSV;

    void parseReservoirs();
    void parseStations();
    void parseCities();
    void parsePipes();

public:
    ParseData(const std::string& reservoirCSV, const std::string& stationsCSV,
              const std::string& citiesCSV, const std::string& pipesCSV);

    const Graph<Code>& getGraph() const { return graph; }
    const DataContainer& getDataContainer() const { return dataContainer; }
};


#endif //PROJ_DA_01_PARSEDATA_H
