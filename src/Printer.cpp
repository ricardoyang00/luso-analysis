#include "Printer.h"
#include <iomanip>
#include <fstream>
#include <cmath>
#include <limits>

using namespace std;

// Function to export reservoir data to a text file
void exportReservoirData(const std::string& filename, const DataContainer& dataContainer) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing!" << std::endl;
        return;
    }

    for (const auto& entry : dataContainer.getReservoirHashTable()) {
        const Reservoir& reservoir = entry.second;
        file << ">> RESERVOIR INFORMATION" << std::endl;
        file << "           Name: " << reservoir.getName() << std::endl;
        file << "   Municipality: " << reservoir.getMunicipality() << std::endl;
        file << "             ID: " << reservoir.getId() << std::endl;
        file << "           Code: " << reservoir.getCode().getCompleteCode() << std::endl;
        file << "   Max Delivery: " << reservoir.getMaxDelivery() << std::endl;
        file << std::endl;
    }

    cout << "Successful: Exported to " + filename << endl;
    file.close();
}

// Function to export station data to a text file
void exportStationData(const std::string& filename, const DataContainer& dataContainer) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing!" << std::endl;
        return;
    }

    for (const auto& entry : dataContainer.getStationHashTable()) {
        const Station& station = entry.second;
        file << ">> STATION INFORMATION" << std::endl;
        file << "         ID: " << station.getId() << std::endl;
        file << "       Code: " << station.getCode().getCompleteCode() << std::endl;
        file << std::endl;
    }

    cout << "Successful: Exported to " + filename << endl;
    file.close();
}

// Function to export city data to a text file
void exportCityData(const std::string& filename, const DataContainer& dataContainer) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing!" << std::endl;
        return;
    }

    for (const auto& entry : dataContainer.getCityHashTable()) {
        const City& city = entry.second;
        file << ">> CITY INFORMATION" << std::endl;
        file << "         City: " << city.getName() << std::endl;
        file << "           ID: " << city.getId() << std::endl;
        file << "         Code: " << city.getCode().getCompleteCode() << std::endl;
        file << "       Demand: " << city.getDemand() << std::endl;
        file << "   Population: " << city.getPopulation() << std::endl;
        file << std::endl;
    }

    cout << "Successful: Exported to " + filename << endl;
    file.close();
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

void printEachPipeInitialMetrics(const Graph<Code>& bsmGraph) {
    double totalDifference = 0;
    double numberOfPipes = 0;
    double maxDif = std::numeric_limits<double>::min();

    std::cout << std::left << std::setw(5) << "Orig";
    std::cout << std::setw(5) << " -> ";
    std::cout << std::setw(5) << "Dest ";
    std::cout << std::setw(10) << " Difference" << std::endl;

    std::cout << "---------------------------" << std::endl;

    for (auto v : bsmGraph.getVertexSet()) {
        for (auto e : v->getAdj()) {
            if (e->getOrig()->getInfo().getNumber() != 0 && e->getDest()->getInfo().getNumber() != 0) {
                double dif = e->getWeight() - e->getFlow();
                std::cout << std::setw(5) << e->getOrig()->getInfo().getCompleteCode();
                std::cout << std::setw(5) << " -> ";
                std::cout << std::setw(5) << e->getDest()->getInfo().getCompleteCode() << "    ";
                std::cout << std::setw(10) << dif << std::endl;
                totalDifference += dif;
                if (dif > maxDif) maxDif = dif;
                if (e->getReverse() == nullptr) numberOfPipes++;
                else numberOfPipes += 0.5;
            }
        }
    }

    std::cout << "\n";
    std::cout << makeBold("Max difference: ") << maxDif << std::endl;
    std::cout << makeBold("Total difference: ") << totalDifference << std::endl;
    double avgDif = totalDifference / numberOfPipes;
    std::cout << makeBold("Average difference: ") << totalDifference << " / 42 (number of pipes) ≈ " << avgDif << std::endl;

    double totalSquaredDif = 0;

    for (auto v : bsmGraph.getVertexSet()) {
        for (auto e : v->getAdj()) {
            if (e->getOrig()->getInfo().getNumber() != 0 && e->getDest()->getInfo().getNumber() != 0) {
                double squaredDif = pow((e->getWeight() - e->getFlow() - avgDif), 2);
                totalSquaredDif += squaredDif;
            }
        }
    }

    std::cout << makeBold("Variance: ") << totalSquaredDif / numberOfPipes << std::endl;
}