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

        getline(ss, nonTrimmed);
        reservoir.setMaxDelivery(stoi(TrimString(nonTrimmed)));

        dataContainer.dataMap[code.getType()].emplace(code.getNumber(), std::move(reservoir));
        codeGraph.addVertex(code);
    }
    file.close();
}

void ParseData::parseStations() {
    ifstream file(stationsCSV);
    if (!file.is_open()) {
        cerr << "ERROR: Unable to open file " << stationsCSV << endl;
        return;
    }

    string line;
    getline(file, line);

    while(getline(file, line)) {
        stringstream ss(line);

        string nonTrimmed;

        Station station;

        getline(ss, nonTrimmed, ',');
        station.setId(stoi(TrimString(nonTrimmed)));

        getline(ss, nonTrimmed);
        Code code = Code(TrimString(nonTrimmed));
        station.setCode(code);

        dataContainer.dataMap[code.getType()].emplace(code.getNumber(), std::move(station));
        codeGraph.addVertex(code);
    }
}

void ParseData::parseCities() {
    ifstream file(citiesCSV);
    if (!file.is_open()) {
        cerr << "ERROR: Unable to open file " << citiesCSV << endl;
        return;
    }

    string line;
    getline(file, line);

    while(getline(file, line)) {
        stringstream ss(line);

        string nonTrimmed;

        City city;

        getline(ss, nonTrimmed, ',');
        city.setName(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        city.setId(stoi(TrimString(nonTrimmed)));

        getline(ss, nonTrimmed, ',');
        Code code = Code(TrimString(nonTrimmed));
        city.setCode(code);

        getline(ss, nonTrimmed, ',');
        city.setDemand(stod(TrimString(nonTrimmed)));

        getline(ss, nonTrimmed);
        string populationStr = TrimString(nonTrimmed);
        populationStr.erase(remove(populationStr.begin(), populationStr.end(), '\"'), populationStr.end());
        populationStr.erase(remove(populationStr.begin(), populationStr.end(), ','), populationStr.end());
        city.setPopulation((stoi(populationStr)));

        dataContainer.dataMap[code.getType()].emplace(code.getNumber(), std::move(city));
        codeGraph.addVertex(code);
    }
}

void ParseData::parsePipes() {
    ifstream file(pipesCSV);
    if (!file.is_open()) {
        cerr << "ERROR: Unable to open file " << pipesCSV << endl;
        return;
    }

    string line;
    getline(file, line);

    while(getline(file, line)) {
        stringstream ss(line);

        string nonTrimmed;

        getline(ss, nonTrimmed, ',');
        Code servicePointA = Code(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        Code servicePointB = Code(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        int capacity = stoi(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        bool direction = stoi(TrimString(nonTrimmed));

        Vertex<Code>* pointA = codeGraph.findVertex(servicePointA);
        Vertex<Code>* pointB = codeGraph.findVertex(servicePointB);

        if (pointA && pointB) {
            direction ? codeGraph.addEdge(servicePointA, servicePointB, capacity)
                      : codeGraph.addBidirectionalEdge(servicePointA, servicePointB, capacity);
        } else {
            cerr << "ERROR: Either point A or point B not found" << endl;
        }
    }
}
