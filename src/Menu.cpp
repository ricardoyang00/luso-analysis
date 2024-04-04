#include "Menu.h"

using namespace std;

string reservoirCSV = "../small-dataSet/Reservoirs_Madeira.csv";
string stationsCSV = "../small-dataSet/Stations_Madeira.csv";
string citiesCSV = "../small-dataSet/Cities_Madeira.csv";
string pipesCSV = "../small-dataSet/Pipes_Madeira.csv";

Menu::Menu() : parser(reservoirCSV, stationsCSV, citiesCSV, pipesCSV), bsm(parser.getCodeGraph(), parser.getDataContainer()){
    menuIndex = {
            makeBold("[1] Total Maximum Flow"),
            makeBold("[2] Cities With Water Deficit"),
            makeBold("[3] Print Each Pipe Flow Difference"),
            makeBold("[4] Remove Reservoir"),
            makeBold("[5] Remove Pumping Station"),
            makeBold("[9] Export Data Container"),
            makeBold("[0] EXIT")
    };
}

void Menu::clearScreen() {
    system("clear || cls");
}

void Menu::waitPress() {
    cout << "\n";
    cin.get();
    cout << "Press ENTER to continue...";
    cin.get();
}

int Menu::inputParser(int& choice, const string& text) {
    cout << "\n" + text;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 1;
    }
    return 0;
}

void Menu::printMenu() {
    cout << "┌───────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << "│   ██╗     ██╗   ██╗███████╗ ██████╗      █████╗ ███╗   ██╗ █████╗ ██╗     ██╗   ██╗████████╗██╗ ██████╗███████╗   │" << endl;
    cout << "│   ██║     ██║   ██║██╔════╝██╔═══██╗    ██╔══██╗████╗  ██║██╔══██╗██║     ╚██╗ ██╔╝╚══██╔══╝██║██╔════╝██╔════╝   │" << endl;
    cout << "│   ██║     ██║   ██║███████╗██║   ██║    ███████║██╔██╗ ██║███████║██║      ╚████╔╝    ██║   ██║██║     ███████╗   │" << endl;
    cout << "│   ██║     ██║   ██║╚════██║██║   ██║    ██╔══██║██║╚██╗██║██╔══██║██║       ╚██╔╝     ██║   ██║██║     ╚════██║   │" << endl;
    cout << "│   ███████╗╚██████╔╝███████║╚██████╔╝    ██║  ██║██║ ╚████║██║  ██║███████╗   ██║      ██║   ██║╚██████╗███████║   │" << endl;
    cout << "│   ╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝     ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝   ╚═╝      ╚═╝   ╚═╝ ╚═════╝╚══════╝   │" << endl;
    cout << "│                                       Portuguese Water Management Tool                                            │" << endl;
    cout << "└──┬────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘" << endl;
    cout << "   │" << endl;
    for (const auto& e : menuIndex) {
        cout << "   │  " << e << endl;
    }
    cout << "   │" << endl;
}

int Menu::run() {
    while (true) {
        clearScreen();
        printMenu();

        int choice;
        if (inputParser(choice, "Enter your choice: ")) continue;

        clearScreen();
        switch (choice) {
            case 0:     // exit
                clearScreen();
                return 0;
            case 1:     // maximum flow all cities (total)
                getTotalMaxFlow();
                printEachCityMaxFlow(bsm.getBSMGraph(), parser.getDataContainer());
                break;
            case 2:     // cities with water deficit
                printCitiesWithWaterFlowDeficit(bsm.getBSMGraph(), parser.getDataContainer());
                break;
            case 3:     // initial metrics
                printEachPipeInitialMetrics(bsm.getBSMGraph());
                break;
            case 4:     // remove reservoir
                clearScreen();
                removeReservoir();
                break;
            case 5:
                clearScreen();
                removePumpingStation();
                break;
            case 9:     // export data container
                printAllDataContainer();
                break;
            default:
                continue;
        }
        waitPress();
    }
}

void Menu::printAllDataContainer() {
    exportReservoirData("../output/data-container/reservoir_dataContainer.txt", parser.getDataContainer());
    exportStationData("../output/data-container/station_dataContainer.txt", parser.getDataContainer());
    exportCityData("../output/data-container/city_dataContainer.txt", parser.getDataContainer());
}

void Menu::getTotalMaxFlow() {
    cout << endl;
    cout << makeBold("Total max flow: ") << bsm.getTotalMaxFlow() << endl;
}

void Menu::removeReservoir() {
    int codeNumber;
    if (inputParser(codeNumber, "Enter the Reservoir ID number (eg. R_9, enter 9): ")) {
        cout << "ERROR: Couldn't find Reservoir" << endl;
    }

    Code reservoirCode("R_" + to_string(codeNumber));

    map<int,double> oldCitiesFlow = bsm.getCitiesFlow();
    map<int,double> newCitiesFlow;

    if (bsm.removeReservoir(reservoirCode)) {
        cerr << "Error: Couldn't run removeReservoir of BSM" << endl;
        return;
    }
    newCitiesFlow = bsm.getCitiesFlow(); //after compile the removeReservoir

    cout << "New Total Max Flow: " << bsm.getTotalMaxFlow() << endl;
    printAffectedCities(oldCitiesFlow, newCitiesFlow);
    bsm.resetBSMGraph();
}

void Menu::removePumpingStation() {
    int codeNumber;
    if (inputParser(codeNumber, "Enter the Pumping Station ID number (eg. PS_9, enter 9): ")) {
        cout << "ERROR: Couldn't find Pumping Station" << endl;
    }

    Code stationCode("PS_" + to_string(codeNumber));

    map<int,double> oldCitiesFlow = bsm.getCitiesFlow();
    map<int,double> newCitiesFlow;

    if (bsm.removePumpingStation(stationCode)) {
        cerr << "Error: Couldn't run removePumpingStation of BSM" << endl;
        return;
    }
    newCitiesFlow = bsm.getCitiesFlow();

    cout << "New Total Max Flow: " << bsm.getTotalMaxFlow() << endl;
    printAffectedCities(oldCitiesFlow, newCitiesFlow);
    bsm.resetBSMGraph();
}

void Menu::printAffectedCities(map<int,double> oldCitiesFlow, map<int,double> newCitiesFlow) {
    vector<pair<City,double>> affectedCities;
    for (auto cityOld : oldCitiesFlow) {
        int cityCodeNumber = cityOld.first;
        double oldFlow = cityOld.second;
        double newFlow = newCitiesFlow[cityCodeNumber];

        if (oldFlow > newFlow) {
            auto cityObj = parser.getDataContainer().getCityHashTable().find(cityCodeNumber)->second;
            affectedCities.emplace_back(cityObj,oldFlow);
        }
    }


    cout << "CITIES AFFECTED: \"< [code] name (new-flow/demand), old-flow >\"" << endl;
    if (affectedCities.empty()) {
        cout << "     --" << endl;
        return;
    }
    int i = 1;
    for (const auto& pair : affectedCities) {
        auto city = pair.first;
        auto oldFlow = pair.second;
        cout << "    " << i++ << ". [" << city.getCode().getCompleteCode() << "] "
             << city.getName() << " (" << bsm.getFlowToCity(city.getCode())
             << "/" << city.getDemand() << "), " << oldFlow << endl;
    }
}
