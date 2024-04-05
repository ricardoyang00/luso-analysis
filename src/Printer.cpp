#include "Printer.h"
#include <iomanip>

#define ALPHABET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ " // space character used on purpose

using namespace std;

// Function to export reservoir data to a text file
void exportReservoirData(const string& filename, const DataContainer& dataContainer) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << " for writing!" << endl;
        return;
    }

    for (const auto& entry : dataContainer.getReservoirHashTable()) {
        const Reservoir& reservoir = entry.second;
        file << ">> RESERVOIR INFORMATION" << endl;
        file << "           Name: " << reservoir.getName() << endl;
        file << "   Municipality: " << reservoir.getMunicipality() << endl;
        file << "             ID: " << reservoir.getId() << endl;
        file << "           Code: " << reservoir.getCode().getCompleteCode() << endl;
        file << "   Max Delivery: " << reservoir.getMaxDelivery() << endl;
        file << endl;
    }

    cout << "Successful: Exported to " + filename << endl;
    file.close();
}

// Function to export station data to a text file
void exportStationData(const string& filename, const DataContainer& dataContainer) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << " for writing!" << endl;
        return;
    }

    for (const auto& entry : dataContainer.getStationHashTable()) {
        const Station& station = entry.second;
        file << ">> STATION INFORMATION" << endl;
        file << "         ID: " << station.getId() << endl;
        file << "       Code: " << station.getCode().getCompleteCode() << endl;
        file << endl;
    }

    cout << "Successful: Exported to " + filename << endl;
    file.close();
}

// Function to export city data to a text file
void exportCityData(const string& filename, const DataContainer& dataContainer) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << " for writing!" << endl;
        return;
    }

    for (const auto& entry : dataContainer.getCityHashTable()) {
        const City& city = entry.second;
        file << ">> CITY INFORMATION" << endl;
        file << "         City: " << city.getName() << endl;
        file << "           ID: " << city.getId() << endl;
        file << "         Code: " << city.getCode().getCompleteCode() << endl;
        file << "       Demand: " << city.getDemand() << endl;
        file << "   Population: " << city.getPopulation() << endl;
        file << endl;
    }

    cout << "Successful: Exported to " + filename << endl;
    file.close();
}

void exportAllCitiesMaxFlow(const string& filename, const Graph<Code>& bsmGraph, const DataContainer& dataContainer) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << " for writing!" << endl;
        return;
    }

    printEachCityMaxFlow(file, bsmGraph, dataContainer);

    cout << "Successful: Exported to " + filename << endl;
    file.close();
}

void printHeader(ostream& output) {
    output << left << setw(20) << "Name" << "|    ";
    output << setw(8) << "Code" << "|    ";
    output << setw(10) << "Max Flow" << endl;

    output << setfill('-') << setw(20) << "" << "|";
    output << setw(12) << "" << "|";
    output << setw(14) << "" << setfill(' ') << endl;
}

void printCityMaxFlow(ostream& output, const string& name, const string& code, const double& maxFlow) {
    int nameWidth = (name.find_first_not_of(ALPHABET) != string::npos) ? 21 : 20;
    output << setw(nameWidth) << name << "|    ";
    output << setw(8) << code << "|    ";
    output << setw(10) << maxFlow << endl;
}

void printEachCityMaxFlow(ostream& output, const Graph<Code>& bsmGraph, const DataContainer& dataContainer) {
    Vertex<Code>* superSink = bsmGraph.findVertex(Code("C_0"));
    if (superSink == nullptr) {
        throw logic_error("Couldn't find super sink C_0");
    }

    auto cTable = dataContainer.getCityHashTable();
    printHeader(output);

    for (const auto& edge : superSink->getIncoming()) {
        auto cityVertex = edge->getOrig()->getInfo();
        auto c = cTable.find(cityVertex.getNumber())->second;

        printCityMaxFlow(output, c.getName(), cityVertex.getCompleteCode(), edge->getFlow());
    }
}

void printSpecificCityMaxFlow(const Graph<Code>& bsmGraph, const DataContainer& dataContainer, const Code& city) {
    Vertex<Code>* superSink = bsmGraph.findVertex(Code("C_0"));
    if (superSink == nullptr) {
        throw logic_error("Couldn't find super sink C_0");
    }

    auto cTable = dataContainer.getCityHashTable();
    printHeader(cout);

    for (const auto& edge : superSink->getIncoming()) {
        auto cityVertex = edge->getOrig()->getInfo();
        if (cityVertex == city) {
            auto c = cTable.find(cityVertex.getNumber())->second;
            printCityMaxFlow(cout, c.getName(), cityVertex.getCompleteCode(), edge->getFlow());
            return;
        }
    }
    throw logic_error("Invalid city chosen");
}

void printCitiesWithWaterFlowDeficit(const Graph<Code>& bsmGraph, const DataContainer& dataContainer) {
    Vertex<Code>* superSink = bsmGraph.findVertex(Code("C_0"));
    if (superSink == nullptr) {
        throw logic_error("Couldn't find super sink C_0");
    }

    auto cTable = dataContainer.getCityHashTable();
    cout << left << setw(20) << "Name" << "|    ";
    cout << setw(8) << "Code" << "|    ";
    cout << setw(10) << "Deficit" << "|    ";
    cout << setw(10) << "Max Flow" << "|    ";
    cout << setw(10) << "Demand" << endl;

    cout << setfill('-') << setw(20) << "" << "|";
    cout << setw(12) << "" << "|";
    cout << setw(14) << "" << "|";
    cout << setw(14) << "" << "|";
    cout << setw(14) << "" << setfill(' ') << endl;

    for (const auto& edge : superSink->getIncoming()) {
        auto cityVertex = edge->getOrig()->getInfo();
        auto c = cTable.find(cityVertex.getNumber())->second;
        if (edge->getFlow() < c.getDemand()) {
            double dif = c.getDemand() - edge->getFlow();
            int nameWidth = (c.getName().find_first_not_of(ALPHABET) != string::npos) ? 21 : 20;
            cout << setw(nameWidth) << c.getName() << "|    ";
            cout << setw(8) << cityVertex.getCompleteCode() << "|    ";
            cout << setw(10) << dif << "|    ";
            cout << setw(10) << edge->getFlow() << "|    ";
            cout << setw(10) << c.getDemand() << endl;
        }
    }
}

void printEachPipeInitialMetrics(const Graph<Code>& bsmGraph) {
    double totalDifference = 0;
    double numberOfPipes = 0;
    double maxDif = numeric_limits<double>::min();

    cout << "\n";
    cout << makeBold("Note: ") << "* represents the pipes that are bidirectional" << endl;
    cout << "\n";

    cout << left << setw(8) << "Orig" << "|    ";
    cout << setw(8) << "Dest" << "|    ";
    cout << setw(16) << "Flow/Capacity" << "|    ";
    cout << setw(10) << "Difference" << endl;

    cout << setfill('-') << setw(8) << "" << "|";
    cout << setw(12) << "" << "|";
    cout << setw(20) << "" << "|";
    cout << setw(16) << "" << setfill(' ') << endl;

    for (auto v : bsmGraph.getVertexSet()) {
        for (auto e : v->getAdj()) {
            if (e->getOrig()->getInfo().getNumber() != 0 && e->getDest()->getInfo().getNumber() != 0) {
                double dif = e->getWeight() - e->getFlow();

                if (e->getReverse() == nullptr) {
                    cout << setw(8) << e->getOrig()->getInfo().getCompleteCode() << "|    ";
                    cout << setw(8) << e->getDest()->getInfo().getCompleteCode() << "|    ";
                    cout << right << setw(3) << e->getFlow() << "/";
                    cout << left << setw(12) << e->getWeight() << "|    ";
                    cout << setw(16) << dif << endl;
                } else {
                    if (e->getFlow() != 0) {
                        cout << "*" << setw(7) << e->getOrig()->getInfo().getCompleteCode() << "|    ";
                        cout << "*" << setw(7) << e->getDest()->getInfo().getCompleteCode() << "|    ";
                        cout << right << setw(3) << e->getFlow() << "/";
                        cout << left << setw(12) << e->getWeight() << "|    ";
                        cout << setw(16) << dif << endl;
                    } else {
                        dif = 0; // exclude the bidirectional edge with no flow
                    }
                }

                numberOfPipes += (e->getReverse() == nullptr) ? 1 : 0.5; // add 0.5 because pipe is bidirectional (summed twice)

                totalDifference += dif;
                if (dif > maxDif) maxDif = dif;
            }
        }
    }

    cout << "\n";
    cout << makeBold("Max difference: ") << maxDif << endl;
    cout << makeBold("Sum of differences: ") << totalDifference << endl;
    double avgDif = totalDifference / numberOfPipes;
    cout << makeBold("Average difference: ") << totalDifference << " / " << numberOfPipes << " (#pipes) ≈ " << avgDif << endl;

    double totalSquaredDif = 0;

    for (auto v : bsmGraph.getVertexSet()) {
        for (auto e : v->getAdj()) {
            if (e->getOrig()->getInfo().getNumber() != 0 && e->getDest()->getInfo().getNumber() != 0) {
                if (e->getReverse() == nullptr || (e->getReverse() != nullptr && e->getFlow() != 0)) {
                    double squaredDif = pow((e->getWeight() - e->getFlow() - avgDif), 2);
                    totalSquaredDif += squaredDif;
                }
            }
        }
    }

    auto variance = static_cast<long long>(totalSquaredDif / numberOfPipes);

    cout << makeBold("Variance: ") << variance << endl;
}

void exportCriticalPipesForEachCity(const string& pathName, const std::map<int,std::vector<std::pair<Code,Code>>>& criticalPipes, const DataContainer& dataContainer) {
    std::ofstream outputFile(pathName);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    // Redirect output to file
    std::ostream& output = outputFile;
    output << "CRITICAL PIPES FOR EACH CITY\n" << endl;
    output << "For each city, determine which pipelines, if ruptured would make it impossible \nto deliver the desired amount of water to a given city.\n" << endl;
    int i = 1;
    for (auto pair : criticalPipes) {
        output << i++ << ". [" << dataContainer.getCityHashTable().find(pair.first)->second.getCode().getCompleteCode()
               << "] " << dataContainer.getCityHashTable().find(pair.first)->second.getName() << " :" << endl;
        int j = 1;
        for (auto city : pair.second) {
            output << "    " << j++ << ". " << city.first.getCompleteCode() << " -> " << city.second.getCompleteCode() << endl;
        }
        output << endl;
    }

    cout << "Successful: Exported to " + pathName << endl;

    outputFile.close();
}