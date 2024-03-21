#include "Printer.h"

using namespace std;

//prints the hash table
void printHashInfo(DataContainer dataContainer, const Code& code) {
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
            cout << "     City Info: " << endl;
            cout << "          City: " << city.getName() << endl;
            cout << "            ID: " << city.getId() << endl;
            cout << "          Code: " << city.getCode().getCompleteCode() << endl;
            cout << fixed << setprecision(2) << "        Demand: " << city.getDemand() << endl;
            cout << "    Population: " << city.getPopulation() << endl;
        }
    } else {
        cout << "ERROR: INVALID CODE TYPE" << endl;
    }
}
/*
//Prints all hash tables
void printAllHashInfo(const DataContainer& dataContainer) {
    // Iterate over the data and output information
    for (const auto& [codeType, innerMap] : dataContainer.dataMap) {
        switch(codeType) {
            case CodeType::RESERVOIR:
                cout << "RESERVOIRS INFORMATION " << endl;
                for (const auto& [key, innerMapValue] : innerMap) {
                    if (std::holds_alternative<Reservoir>(innerMapValue)) {
                        const Reservoir& reservoir = std::get<Reservoir>(innerMapValue);
                        cout << "   Reservoir Key: " << key << endl;
                        cout << "            Name: " << reservoir.getName() << endl;
                        cout << "    Municipality: " << reservoir.getMunicipality() << endl;
                        cout << "              ID: " << reservoir.getId() << endl;
                        cout << "            Code: " << reservoir.getCode().getCompleteCode() << endl;
                        cout << "    Max Delivery: " << reservoir.getMaxDelivery() << endl;
                        cout << endl;
                    }
                }
                cout << "-------------------------------------\n" << endl;
                break;
            case CodeType::STATION:
                cout << "PIPE STATIONS INFORMATION: " << endl;
                for (const auto& [key, innerMapValue] : innerMap) {
                    if (std::holds_alternative<Station>(innerMapValue)) {
                        const Station& station = std::get<Station>(innerMapValue);
                        cout << "Key: " << key << endl;
                        cout << "      ID: " << station.getId() << endl;
                        cout << "    Code: " << station.getCode().getCompleteCode() << endl;
                        cout << endl;
                    }
                }
                cout << "-------------------------------------\n" << endl;
                break;
            case CodeType::CITY:
                cout << "Cities: " << endl;
                for (const auto& [key, innerMapValue] : innerMap) {
                    if (std::holds_alternative<City>(innerMapValue)) {
                        const City& city = std::get<City>(innerMapValue);
                        cout << "Key: " << key << endl;
                        cout << "          City: " << city.getName() << endl;
                        cout << "            ID: " << city.getId() << endl;
                        cout << "          Code: " << city.getCode().getCompleteCode() << endl;
                        cout << fixed << setprecision(2) << "        Demand: " << city.getDemand() << endl;
                        cout << "    Population: " << city.getPopulation() << endl;
                        cout << endl;
                    }
                }
                cout << "-------------------------------------\n" << endl;
                break;
            default:
                cerr << "ERROR" << endl;
                break;
        }
    }
}*/