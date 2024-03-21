#include <iostream>
#include "BasicServiceMetrics.h"
#include "Printer.h"

using namespace std;

int main() {

    std::string reservoirCSV = "../small-dataSet/Reservoirs_Madeira.csv";
    std::string stationsCSV = "../small-dataSet/Stations_Madeira.csv";
    std::string citiesCSV = "../small-dataSet/Cities_Madeira.csv";
    std::string pipesCSV = "../small-dataSet/Pipes_Madeira.csv";
    /*std::string reservoirCSV = "../large-dataSet/Reservoir.csv";
    std::string stationsCSV = "../large-dataSet/Stations.csv";
    std::string citiesCSV = "../large-dataSet/Cities.csv";
    std::string pipesCSV = "../large-dataSet/Pipes.csv";*/
    ParseData parser(reservoirCSV, stationsCSV, citiesCSV, pipesCSV);

    const DataContainer& dataContainer = parser.getDataContainer();

    printHashInfo(dataContainer, Code("PS_3"));
    //printAllHashInfo(dataContainer);

    /*
    for (const auto& v : parser.getCodeGraph().getVertexSet()) {
        for (const auto& e : v->getAdj()) {
            cout << "Origin: " << e->getOrig()->getInfo().getCompleteCode() << endl;
            cout << "Dest: " << e->getDest()->getInfo().getCompleteCode() << endl;
            cout << "Capacity: " << e->getWeight() << endl;
            cout << "Flow: " << e->getFlow() << endl;
            cout << "--------------------------------\n" << endl;
        }
    }*/

    BasicServiceMetrics bsm(parser.getCodeGraph(), dataContainer);

    bsm.edmondsKarpSpecific(Code("R_1"), Code("C_5"));
    bsm.edmondsKarpAllCities(Code("R_1"));

    stringstream ss;

    // print info for specific
    /*for(auto v : parser.getCodeGraph().getVertexSet()) {
        ss.str("");
        bool hasContent = false;
        for (const auto e : v->getAdj())
            if (e->getFlow() != 0) {
                ss << e->getDest()->getInfo().getCompleteCode() << "[Flow: " << e->getFlow() << "]";
                hasContent = true;
            } else continue;
        ss << ")";
        if (hasContent) cout << v->getInfo().getCompleteCode() << "->(" << ss.str() << endl;
    }*/

    // print info for all cities
    for (auto v : parser.getCodeGraph().getVertexSet()) {
        if (v->getInfo().getType() == CodeType::CITY) {
            for (const auto e : v->getIncoming()) {
                cout << e->getDest()->getInfo().getCompleteCode() << "[Flow: " << e->getFlow() << "]" << endl;
            }
        }
    }

    return 0;
}
