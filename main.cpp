#include <iostream>
#include "BasicServiceMetrics.h"
#include "Printer.h"

using namespace std;

int main() {

    /*std::string reservoirCSV = "../small-dataSet/Reservoirs_Madeira.csv";
    std::string stationsCSV = "../small-dataSet/Stations_Madeira.csv";
    std::string citiesCSV = "../small-dataSet/Cities_Madeira.csv";
    std::string pipesCSV = "../small-dataSet/Pipes_Madeira.csv";*/

    std::string reservoirCSV = "../large-dataSet/Reservoir.csv";
    std::string stationsCSV = "../large-dataSet/Stations.csv";
    std::string citiesCSV = "../large-dataSet/Cities.csv";
    std::string pipesCSV = "../large-dataSet/Pipes.csv";

    ParseData parser(reservoirCSV, stationsCSV, citiesCSV, pipesCSV);

    const DataContainer& dataContainer = parser.getDataContainer();

    //printHashInfo(dataContainer, Code("C_3"));
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

    bsm.edmondsKarp();

    cout << bsm.getTotalMaxFlow() << endl;
    //bsm.printSpecific();

    return 0;
}
