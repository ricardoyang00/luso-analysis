#include <iostream>
#include "ParseData.h"
#include <iomanip>

using namespace std;

void PrintInfo(const DataContainer& dataContainer, const Code& code) {
    auto type = dataContainer.dataMap.find(code.getType());
    if (type != dataContainer.dataMap.end()) {
        auto innerMap = type->second.find(code.getNumber());
        if (innerMap != type->second.end()) {
            switch(code.getType()) {
                case CodeType::RESERVOIR: {
                    const Reservoir& reservoir = get<Reservoir>(innerMap->second);
                    cout << "Reservoir Info: " << endl;
                    cout << "    Name: " << reservoir.getName() << endl;
                    cout << "    Municipality: " << reservoir.getMunicipality() << endl;
                    cout << "    ID: " << reservoir.getId() << endl;
                    cout << "    Code: " << reservoir.getCode().getCompleteCode() << endl;
                    cout << "    Max Delivery: " << reservoir.getMaxDelivery() << endl;
                    break;
                }
                case CodeType::STATION: {
                    const Station& station = get<Station>(innerMap->second);
                    cout << "Pipe Station Info: " << endl;
                    cout << "    ID: " << station.getId() << endl;
                    cout << "    Code: " << station.getCode().getCompleteCode() << endl;
                    break;
                }
                case CodeType::CITY: {
                    const City& city = get<City>(innerMap->second);
                    cout << "City Info: " << endl;
                    cout << "    City: " << city.getName() << endl;
                    cout << "    ID: " << city.getId() << endl;
                    cout << "    Code: " << city.getCode().getCompleteCode() << endl;
                    cout << fixed << setprecision(2) << "    Demand: " << city.getDemand() << endl;
                    cout << "    Population: " << city.getPopulation() << endl;
                    break;
                }
            }
        } else {
            cout << "Id " << code.getNumber() << " not found for CodeType " << code.codeTypeToString() << endl;
        }
    } else {
        cout << "CodeType not found: " << code.codeTypeToString() << endl;
    }
}

void PrintAllInfo(const DataContainer& dataContainer) {
    // Iterate over the data and output information
    for (const auto& [codeType, innerMap] : dataContainer.dataMap) {
        switch(codeType) {
            case CodeType::RESERVOIR:
                cout << "Reservoirs: " << endl;
                for (const auto& [key, innerMapValue] : innerMap) {
                    if (std::holds_alternative<Reservoir>(innerMapValue)) {
                        const Reservoir& reservoir = std::get<Reservoir>(innerMapValue);
                        cout << "Key: " << key << endl;
                        cout << "    Name: " << reservoir.getName() << endl;
                        cout << "    Municipality: " << reservoir.getMunicipality() << endl;
                        cout << "    ID: " << reservoir.getId() << endl;
                        cout << "    Code: " << reservoir.getCode().getCompleteCode() << endl;
                        cout << "    Max Delivery: " << reservoir.getMaxDelivery() << endl;
                    }
                }
                break;
            case CodeType::STATION:
                cout << "Stations: " << endl;
                for (const auto& [key, innerMapValue] : innerMap) {
                    if (std::holds_alternative<Station>(innerMapValue)) {
                        const Station& station = std::get<Station>(innerMapValue);
                        cout << "Key: " << key << endl;
                        cout << "    ID: " << station.getId() << endl;
                        cout << "    Code: " << station.getCode().getCompleteCode() << endl;
                    }
                }
                break;
            case CodeType::CITY:
                cout << "Cities: " << endl;
                for (const auto& [key, innerMapValue] : innerMap) {
                    if (std::holds_alternative<City>(innerMapValue)) {
                        const City& city = std::get<City>(innerMapValue);
                        cout << "Key: " << key << endl;
                        cout << "    City: " << city.getName() << endl;
                        cout << "    ID: " << city.getId() << endl;
                        cout << "    Code: " << city.getCode().getCompleteCode() << endl;
                        cout << fixed << setprecision(2) << "    Demand: " << city.getDemand() << endl;
                        cout << "    Population: " << city.getPopulation() << endl;
                    }
                }
                break;
            default:
                cerr << "ERROR" << endl;
                break;
        }
    }
}

int main() {
    std::string reservoirCSV = "../small-dataSet/Reservoirs_Madeira.csv";
    std::string stationsCSV = "../small-dataSet/Stations_Madeira.csv";
    std::string citiesCSV = "../small-dataSet/Cities_Madeira.csv";
    std::string pipesCSV = "../small-dataSet/Pipes_Madeira.csv";
    ParseData parser(reservoirCSV, stationsCSV, citiesCSV, pipesCSV);

    const DataContainer& dataContainer = parser.getDataContainer();

    PrintInfo(dataContainer, Code("PS_3"));

    //PrintAllInfo(dataContainer);

    return 0;
}
