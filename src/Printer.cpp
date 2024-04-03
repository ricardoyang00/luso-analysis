#include "Printer.h"
#include <iomanip>
#include <cmath>

using namespace std;

//prints the hash table
void printHashInfo(const DataContainer& dataContainer, const Code& code) {
    if (code.getType() == CodeType::RESERVOIR) {
        auto ReservoirHashTable = dataContainer.getReservoirHashTable();
        auto reservoir_it = ReservoirHashTable.find(code.getNumber());

        if (reservoir_it != ReservoirHashTable.end()) {
            auto reservoir = reservoir_it->second;
            cout << "RESERVOIR INFORMATION: " << endl;
            cout << "          Name: " << reservoir.getName() << endl;
            cout << "  Municipality: " << reservoir.getMunicipality() << endl;
            cout << "            ID: " << reservoir.getId() << endl;
            cout << "          Code: " << reservoir.getCode().getCompleteCode() << endl;
            cout << "  Max Delivery: " << reservoir.getMaxDelivery() << endl;
        }
    } else if (code.getType() == CodeType::STATION) {
        auto StationHashTable = dataContainer.getStationHashTable();
        auto station_it = StationHashTable.find(code.getNumber());

        if (station_it != StationHashTable.end()) {
            auto station = station_it->second;
            cout << "PIPE STATION INFORMATION: " << endl;
            cout << "      ID: " << station.getId() << endl;
            cout << "    Code: " << station.getCode().getCompleteCode() << endl;
        }
    } else if (code.getType() == CodeType::CITY) {
        auto CityHashTable = dataContainer.getCityHashTable();
        auto city_it = CityHashTable.find(code.getNumber());

        if (city_it != CityHashTable.end()) {
            auto city = city_it->second;
            cout << "CITY INFORMATION: " << endl;
            cout << "          City: " << city.getName() << endl;
            cout << "            ID: " << city.getId() << endl;
            cout << "          Code: " << city.getCode().getCompleteCode() << endl;
            cout << fixed << setprecision(2) << "        Demand: " << city.getDemand() << endl;
            cout << "    Population: " << city.getPopulation() << endl;
        }
    } else {
        cout << "ERROR: INVALID CODE TYPE" << endl;
    }
    cout << endl;
}

void printAllHashInfo(const DataContainer& dataContainer) {
    cout << "RESERVOIR HASH TABLE:" << endl;
    auto reservoirHashTable = dataContainer.getReservoirHashTable();
    for (const auto& pair : reservoirHashTable) {
        const auto& reservoir_code = pair.second.getCode();
        printHashInfo(dataContainer, reservoir_code);
    }

    cout << "STATION HASH TABLE:" << endl;
    auto stationHashTable = dataContainer.getStationHashTable();
    for (const auto& pair : stationHashTable) {
        const auto& station_code = pair.second.getCode();
        printHashInfo(dataContainer, station_code);
    }

    cout << "CITY HASH TABLE:" << endl;
    auto cityHashTable = dataContainer.getCityHashTable();
    for (const auto& pair : cityHashTable) {
        const auto& city_code = pair.second.getCode();
        printHashInfo(dataContainer, city_code);
    }
}

void printHeader() {
    std::cout << std::left << std::setw(20) << "Name" << "|    ";
    std::cout << std::setw(8) << "Code" << "|    ";
    std::cout << std::setw(10) << "Max Flow" << std::endl;

    std::cout << std::setfill('-') << std::setw(20) << "" << "|";
    std::cout << std::setw(12) << "" << "|";
    std::cout << std::setw(14) << "" << std::setfill(' ') << std::endl;
}

void printCityMaxFlow(const std::string& name, const std::string& code, const double& maxFlow) {
    int nameWidth = (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != std::string::npos) ? 21 : 20;
    std::cout << std::setw(nameWidth) << name << "|    ";
    std::cout << std::setw(8) << code << "|    ";
    std::cout << std::setw(10) << maxFlow << std::endl;
}

void printEachCityMaxFlow(const Graph<Code>& bsmGraph, const DataContainer& dataContainer) {
    Vertex<Code>* superSink = bsmGraph.findVertex(Code("C_0"));
    if (superSink == nullptr) {
        throw std::logic_error("Couldn't find super sink C_0");
    }

    auto cTable = dataContainer.getCityHashTable();
    printHeader();

    for (const auto& edge : superSink->getIncoming()) {
        auto cityVertex = edge->getOrig()->getInfo();
        auto c = cTable.find(cityVertex.getNumber())->second;

        printCityMaxFlow(c.getName(), cityVertex.getCompleteCode(), edge->getFlow());
    }
}

void printSpecificCityMaxFlow(const Graph<Code>& bsmGraph, const DataContainer& dataContainer, const Code& city) {
    Vertex<Code>* superSink = bsmGraph.findVertex(Code("C_0"));
    if (superSink == nullptr) {
        throw std::logic_error("Couldn't find super sink C_0");
    }

    auto cTable = dataContainer.getCityHashTable();
    printHeader();

    for (const auto& edge : superSink->getIncoming()) {
        auto cityVertex = edge->getOrig()->getInfo();
        if (cityVertex == city) {
            auto c = cTable.find(cityVertex.getNumber())->second;
            printCityMaxFlow(c.getName(), cityVertex.getCompleteCode(), edge->getFlow());
            return;
        }
    }
    throw std::logic_error("Invalid city chosen");
}

void printCitiesWithWaterFlowDeficit(const Graph<Code>& bsmGraph, const DataContainer& dataContainer) {
    Vertex<Code>* superSink = bsmGraph.findVertex(Code("C_0"));
    if (superSink == nullptr) {
        throw std::logic_error("Couldn't find super sink C_0");
    }

    auto cTable = dataContainer.getCityHashTable();
    std::cout << std::left << std::setw(20) << "Name" << "|    ";
    std::cout << std::setw(8) << "Code" << "|    ";
    std::cout << std::setw(10) << "Deficit" << "|    ";
    std::cout << std::setw(10) << "Max Flow" << "|    ";
    std::cout << std::setw(10) << "Demand" << std::endl;

    std::cout << std::setfill('-') << std::setw(20) << "" << "|";
    std::cout << std::setw(12) << "" << "|";
    std::cout << std::setw(14) << "" << "|";
    std::cout << std::setw(14) << "" << "|";
    std::cout << std::setw(14) << "" << std::setfill(' ') << std::endl;

    for (const auto& edge : superSink->getIncoming()) {
        auto cityVertex = edge->getOrig()->getInfo();
        auto c = cTable.find(cityVertex.getNumber())->second;
        if (edge->getFlow() < c.getDemand()) {
            double dif = c.getDemand() - edge->getFlow();
            int nameWidth = (c.getName().find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != std::string::npos) ? 21 : 20;
            std::cout << std::setw(nameWidth) << c.getName() << "|    ";
            std::cout << std::setw(8) << cityVertex.getCompleteCode() << "|    ";
            std::cout << std::setw(10) << dif << "|    ";
            std::cout << std::setw(10) << edge->getFlow() << "|    ";
            std::cout << std::setw(10) << c.getDemand() << std::endl;
        }
    }
}

void printEachPipeDifference(const Graph<Code>& bsmGraph) {
    double totalDifference = 0;
    std::cout << std::left << std::setw(5) << "Orig";
    std::cout << std::setw(5) << " -> ";
    std::cout << std::setw(5) << "Dest ";
    std::cout << std::setw(10) << " Difference" << std::endl;

    std::cout << "---------------------------" << std::endl;

    for (auto v : bsmGraph.getVertexSet()) {
        for (auto e : v->getAdj()) {
            if (e->getOrig()->getInfo().getNumber() != 0 && e->getDest()->getInfo().getNumber() != 0) {
                std::cout << std::setw(5) << e->getOrig()->getInfo().getCompleteCode();
                std::cout << std::setw(5) << " -> ";
                std::cout << std::setw(5) << e->getDest()->getInfo().getCompleteCode() << "    ";
                std::cout << std::setw(10) << e->getWeight() - e->getFlow() << std::endl;
                totalDifference += e->getWeight() - e->getFlow();
            }
        }
    }

    std::cout << "\n";
    std::cout << makeBold("Total difference: ") << totalDifference << std::endl;
    double avgDif = totalDifference / 42.0;
    std::cout << makeBold("Average difference: ") << totalDifference << " / 42 (number of pipes) ≈ " << avgDif << std::endl;

    double total = 0;
    for (auto v : bsmGraph.getVertexSet()) {
        for (auto e : v->getAdj()) {
            if (e->getOrig()->getInfo().getNumber() != 0 && e->getDest()->getInfo().getNumber() != 0) {
                total += pow((e->getWeight() - e->getFlow() - avgDif), 2);
            }
        }
    }

    std::cout << makeBold("Variance: ") << total / 42.0 << std::endl;
}