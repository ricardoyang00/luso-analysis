#include "ParseData.h"

using namespace std;

DataContainer::DataContainer() {}

unordered_map<int, Reservoir> DataContainer::getReservoirHashTable() const{
    return ReservoirHashTable;
}

unordered_map<int, Station> DataContainer::getStationHashTable() const {
    return StationHashTable;
}

unordered_map<int, City> DataContainer::getCityHashTable() const {
    return CityHashTable;
}

void DataContainer::addToReservoirHashTable(Code code, Reservoir reservoir) {
    ReservoirHashTable[code.getNumber()] = reservoir;
}

void DataContainer::addToStationHashTable(Code code, Station station) {
    StationHashTable[code.getNumber()] = station;
}

void DataContainer::addToCityHashTable(Code code, City city) {
    CityHashTable[code.getNumber()] = city;
}

ParseData::ParseData(const std::string &reservoirCSV, const std::string &stationsCSV, const std::string &citiesCSV, const std::string &pipesCSV) {
    this->reservoirCSV = reservoirCSV;
    this->stationsCSV = stationsCSV;
    this->citiesCSV = citiesCSV;
    this->pipesCSV = pipesCSV;
    parseReservoirs();
    parseStations();
    parseCities();
    parsePipes();

    makeSuperSourceSinkGraph();
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

        dataContainer.addToReservoirHashTable(code, reservoir);
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

        dataContainer.addToStationHashTable(code, station);
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

        dataContainer.addToCityHashTable(code, city);
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

void ParseData::makeSuperSourceSinkGraph() {
    // add super source
    codeGraph.addVertex(Code("R_0"));
    auto superSource = codeGraph.findVertex(Code("R_0"));
    if (superSource == nullptr) {
        throw std::logic_error("Super source R_0 not found in graph");
    }
    auto rTable = dataContainer.getReservoirHashTable();
    for (auto reservoir : codeGraph.getVertexSet()) {
        if (reservoir->getInfo().getType() == CodeType::RESERVOIR && reservoir != superSource) {
            auto r = rTable.find(reservoir->getInfo().getNumber())->second;
            codeGraph.addEdge(superSource->getInfo(), reservoir->getInfo(), r.getMaxDelivery());
        }
    }

    // add super sink
    codeGraph.addVertex(Code("C_0"));
    auto superSink = codeGraph.findVertex(Code("C_0"));
    if (superSink == nullptr) {
        throw std::logic_error("Super sink C_0 not found in graph");
    }
    auto cTable = dataContainer.getCityHashTable();
    for (auto city : codeGraph.getVertexSet()) {
        if (city->getInfo().getType() == CodeType::CITY && city != superSink) {
            auto c = cTable.find(city->getInfo().getNumber())->second;
            codeGraph.addEdge(city->getInfo(), superSink->getInfo(), c.getDemand());
        }
    }
}
