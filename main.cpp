#include <iostream>
#include "ParseData.h"

using namespace std;

int main() {
    std::string reservoirCSV = "small-dataSet/Reservoirs_Madeira.csv";
    std::string stationsCSV = "small-dataSet/Stations_Madeira.csv";
    std::string citiesCSV = "small-dataSet/Cities_Madeira.csv";
    std::string pipesCSV = "small-dataSet/Pipes_Madeira.csv";
    ParseData parser(reservoirCSV, stationsCSV, citiesCSV, pipesCSV);

    const DataContainer& dataContainer = parser.getDataContainer();

    // Iterate over the data and output information
    for (const auto& [codeType, innerMap] : dataContainer.dataMap) {
        if (codeType == CodeType::RESERVOIR) {
            cout << "Reservoirs:" << endl;

            for (const auto& [key, innerMapValue] : innerMap) {
                cout << "  Key: " << key << endl;

                // Check the type of innerMapValue using std::holds_alternative
                if (std::holds_alternative<Reservoir>(innerMapValue)) {
                    const Reservoir& reservoir = std::get<Reservoir>(innerMapValue);
                    cout << "    Reservoir: " << reservoir.getName() << ", Municipality: " << reservoir.getMunicipality()
                    << ", Id: " << reservoir.getId() << ", Code: " << reservoir.getCode().getCode() << ", MD: " << reservoir.getMaxDelivery() << endl;
                }
            }
        }
    }

    return 0;
}
