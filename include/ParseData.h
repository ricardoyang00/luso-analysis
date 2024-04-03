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
#include <iostream>

class DataContainer {
private:
    std::unordered_map<int, Reservoir> ReservoirHashTable;
    std::unordered_map<int, Station> StationHashTable;
    std::unordered_map<int, City> CityHashTable;

public:
    DataContainer();
    std::unordered_map<int, Reservoir> getReservoirHashTable() const;
    std::unordered_map<int, Station> getStationHashTable() const;
    std::unordered_map<int, City> getCityHashTable() const;

    void addToReservoirHashTable(Code code, Reservoir reservoir);
    void addToStationHashTable(Code code, Station station);
    void addToCityHashTable(Code code, City city);
};

class ParseData {
private:
    Graph<Code> codeGraph;
    DataContainer dataContainer;
    std::string reservoirCSV;
    std::string stationsCSV;
    std::string citiesCSV;
    std::string pipesCSV;

    void parseReservoirs();
    void parseStations();
    void parseCities();
    void parsePipes();

    void makeSuperSourceSinkGraph();

public:
    ParseData(const std::string& reservoirCSV, const std::string& stationsCSV,
              const std::string& citiesCSV, const std::string& pipesCSV);

    const Graph<Code>& getCodeGraph() const { return codeGraph; }
    const DataContainer& getDataContainer() const { return dataContainer; }
};


#endif //PROJ_DA_01_PARSEDATA_H
