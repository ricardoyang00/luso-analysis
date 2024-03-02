#include <iostream>
#include "ParseData.h"

using namespace std;

void PrintInfo(const DataContainer& dataContainer, const Code& code) {
    auto type = dataContainer.dataMap.find(code.getType());
    if (type != dataContainer.dataMap.end()) {
        auto innerMap = type->second.find(code.getNumber());
        if (innerMap != type->second.end()) {
            const Reservoir& reservoir = get<Reservoir>(innerMap->second);

            cout << "Reservoir Info: " << endl;
            cout << "    Name: " << reservoir.getName() << endl;
            cout << "    Municipality: " << reservoir.getMunicipality() << endl;
            cout << "    ID: " << reservoir.getId() << endl;
            cout << "    Code: " << reservoir.getCode().getCompleteCode() << endl;
            cout << "    Max Delivery: " << reservoir.getMaxDelivery() << endl;
        } else {
            cout << "Id " << code.getNumber() << " not found for CodeType " << code.codeTypeToString() << endl;
        }
    } else {
        cout << "CodeType not found: " << code.codeTypeToString() << endl;
    }
}

int main() {
    std::string reservoirCSV = "../small-dataSet/Reservoirs_Madeira.csv";
    std::string stationsCSV = "../small-dataSet/Stations_Madeira.csv";
    std::string citiesCSV = "../small-dataSet/Cities_Madeira.csv";
    std::string pipesCSV = "../small-dataSet/Pipes_Madeira.csv";
    ParseData parser(reservoirCSV, stationsCSV, citiesCSV, pipesCSV);

    const DataContainer& dataContainer = parser.getDataContainer();

    PrintInfo(dataContainer, Code("R_3"));

    /*// Iterate over the data and output information
    for (const auto& [codeType, innerMap] : dataContainer.dataMap) {
        if (codeType == CodeType::RESERVOIR) {
            cout << "Reservoirs:" << endl;

            for (const auto& [key, innerMapValue] : innerMap) {
                cout << "  Key: " << key << endl;

                // Check the type of innerMapValue using std::holds_alternative
                if (std::holds_alternative<Reservoir>(innerMapValue)) {
                    const Reservoir& reservoir = std::get<Reservoir>(innerMapValue);
                    cout << "    Reservoir: " << reservoir.getName() << ", Municipality: " << reservoir.getMunicipality()
                    << ", Id: " << reservoir.getId() << ", Code: " << reservoir.getCode().getCompleteCode() << ", MD: " << reservoir.getMaxDelivery() << endl;
                }
            }
        }
    }*/

    return 0;
}
