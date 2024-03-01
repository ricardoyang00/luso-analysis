#include "ParseData.h"

using namespace std;

ParseData::ParseData(const std::string &reservoirCSV, const std::string &stationsCSV, const std::string &citiesCSV, const std::string &pipesCSV) {
    this->reservoirCSV = reservoirCSV;
    this->stationsCSV = stationsCSV;
    this->citiesCSV = citiesCSV;
    this->pipesCSV = pipesCSV;
    parseReservoirs();
    parseStations();
    parseCities();
    parsePipes();
}

void ParseData::parseReservoirs() {
    ifstream file(reservoirCSV);
    if (!file.is_open()) {
        cerr << "ERROR: Unable to open file " << reservoirCSV << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);

        string nonTrimmed;

        Reservoir reservoir;

        getline(ss, nonTrimmed, ',');
        reservoir.setName(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        reservoir.setMunicipality(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        reservoir.setId(stoi(TrimString(nonTrimmed)));

        getline(ss, nonTrimmed, ',');
        Code code = Code(TrimString(nonTrimmed));
        reservoir.setCode(code);

        getline(ss, nonTrimmed, ',');
        reservoir.setMaxDelivery(stoi(TrimString(nonTrimmed)));

        getline(ss, nonTrimmed, ',');

        dataContainer.dataMap[code.getType()].emplace(code.getNumber(), std::move(reservoir));
    }
    file.close();
}