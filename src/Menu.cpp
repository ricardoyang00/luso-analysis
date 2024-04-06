#include "Menu.h"

using namespace std;

Menu::Menu(const std::string& r, const std::string& s, const std::string& c, const std::string& p) : parser(r, s, c, p), bsm(parser.getCodeGraph(), parser.getDataContainer()){
    menuIndex = {
            makeBold("[1] Specific City Maximum Flow"),
            makeBold("[2] Total Maximum Flow"),
            makeBold("[3] Cities With Water Deficit"),
            makeBold("[4] Each Pipe Flow Difference And Initial Metrics"),
            makeBold("[5] Balance Graph"),
            makeBold("[6] Remove Reservoir"),
            makeBold("[7] Remove Pumping Station"),
            makeBold("[8] Remove Pipes"),
            makeBold("[9] Export All Cities Max Flow"),
            makeBold("[10] Export Critical Pipes per City"),
            makeBold("[11] Export Data Container"),
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
            case 1:
                printSpecificCityFlow();
                break;
            case 2:     // maximum flow all cities (total)
                getTotalMaxFlow();
                printEachCityMaxFlow(cout, bsm.getBSMGraph(), parser.getDataContainer());
                break;
            case 3:     // cities with water deficit
                printCitiesWithWaterFlowDeficit(bsm.getBSMGraph(), parser.getDataContainer());
                break;
            case 4:     // metrics
                printEachPipeMetrics(bsm.getBSMGraph());
                break;
            case 5:
                bsm.balanceFlow();
                cout << "Balance algorithm successfully terminated, please check [4] again to see the differences" << endl;
                cout << makeBold("⚠\uFE0FAFTER THIS PLEASE ENSURE THAT YOU RESET THE GRAPH TO AS IT WAS BY CLICKIG [2] Total Maximum Flow⚠\uFE0F") << endl;
                break;
            case 6:     // remove reservoir
                clearScreen();
                removeReservoir();
                break;
            case 7:
                clearScreen();
                removePumpingStation();
                break;
            case 8:
                clearScreen();
                removePipes();
                break;
            case 9:
                exportAllCitiesMaxFlow("../output/allCitiesMaxFlow.txt", bsm.getBSMGraph(), parser.getDataContainer());
                break;
            case 10:
                criticalPipes();
                break;
            case 11:     // export data container
                printAllDataContainer();
                break;
            default:
                continue;
        }
        waitPress();
    }
}

void Menu::printAllDataContainer() {
    exportReservoirData("../output/dataContainer_reservoir.txt", parser.getDataContainer());
    exportStationData("../output/dataContainer_station.txt", parser.getDataContainer());
    exportCityData("../output/dataContainer_city.txt", parser.getDataContainer());
}

void Menu::getTotalMaxFlow() {
    cout << endl;
    cout << makeBold("Total max flow: ") << bsm.getTotalMaxFlow() << endl;
}

void Menu::printSpecificCityFlow() {
    int codeNumber;
    if (inputParser(codeNumber, "Enter the City ID number (eg. C_9, enter 9): ")) {
        cout << "ERROR: Couldn't find Reservoir" << endl;
        return;
    }

    Code cityCode("C_" + to_string(codeNumber));

    printSpecificCityMaxFlow(bsm.getBSMGraph(), parser.getDataContainer(), cityCode);
}

void Menu::removeReservoir() {
    int codeNumber;
    if (inputParser(codeNumber, "Enter the Reservoir ID number (eg. R_9, enter 9): ")) {
        cout << "ERROR: Couldn't find Reservoir" << endl;
        return;
    }

    Code reservoirCode("R_" + to_string(codeNumber));

    map<int,double> oldCitiesFlow = bsm.getCitiesFlow();
    map<int,double> newCitiesFlow;

    bsm.removeReservoir(reservoirCode);
    newCitiesFlow = bsm.getCitiesFlow(); //after compile the removeReservoir

    cout << "New Total Max Flow: " << bsm.getTotalMaxFlow() << endl;
    printAffectedCities(oldCitiesFlow, newCitiesFlow);
    bsm.resetBSMGraph();
}

void Menu::removePumpingStation() {
    int codeNumber;
    if (inputParser(codeNumber, "Enter the Pumping Station ID number (eg. PS_9, enter 9): ")) {
        cout << "ERROR: Couldn't find Pumping Station" << endl;
        return;
    }

    Code stationCode("PS_" + to_string(codeNumber));

    map<int,double> oldCitiesFlow = bsm.getCitiesFlow();
    map<int,double> newCitiesFlow;

    bsm.removePumpingStation(stationCode);
    newCitiesFlow = bsm.getCitiesFlow();

    cout << "New Total Max Flow: " << bsm.getTotalMaxFlow() << endl;
    printAffectedCities(oldCitiesFlow, newCitiesFlow);
    bsm.resetBSMGraph();
}

void Menu::removePipes() {
    vector<pair<Code,Code>> codePipes; // pair of pipe (can be any direction)

    while (true) {
        clearScreen();

        int codeNumber;
        int typeChoice;

        string type;

        cout << "Pipe from: " << makeBold("⚠\uFE0F[Enter 0 to finish the input]⚠\uFE0F") << endl;
        cout << "  1. [R] Reservoir \n  2. [PS] Pumping Station \n  3. [C] City \n" << endl;
        if (inputParser(typeChoice, "Your choice type: ")) {
            cout << "Error: Invalid choice" << endl;
            continue;
        }

        if (typeChoice == 0) break;

        if (typeChoice == 1) type = "R_";
        else if (typeChoice == 2) type = "PS_";
        else if (typeChoice == 3) type = "C_";
        else {
            cout << "Error: Invalid choice" << endl;
            continue;
        }

        if (inputParser(codeNumber, "Enter the ID number (eg. PS_9, enter 9): ")) {
            cout << "ERROR: Couldn't find this ID number" << endl;
            continue;
        }

        Code fromCode(type + to_string(codeNumber));

        cout << "Pipe To: " << endl;
        cout << "  1. [R] Reservoir \n  2. [PS] Pumping Station \n  3. [C] City \n" << endl;
        if (inputParser(typeChoice, "Your choice type: ")) {
            cout << "Error: Invalid choice" << endl;
            continue;
        }

        if (typeChoice == 1) type = "R_";
        else if (typeChoice == 2) type = "PS_";
        else if (typeChoice == 3) type = "C_";
        else {
            cout << "Error: Invalid choice" << endl;
            continue;
        }

        if (inputParser(codeNumber, "Enter the ID number (eg. PS_9, enter 9): ")) {
            cout << "ERROR: Couldn't find this ID number" << endl;
            continue;
        }

        Code toCode(type + to_string(codeNumber));

        codePipes.emplace_back(fromCode, toCode);
    }

    if (!codePipes.empty()) {
        map<int,double> oldCitiesFlow = bsm.getCitiesFlow();
        map<int,double> newCitiesFlow;

        bsm.removePipes(codePipes);
        newCitiesFlow = bsm.getCitiesFlow();

        cout << "New Total Max Flow: " << bsm.getTotalMaxFlow() << endl;
        printAffectedCities(oldCitiesFlow, newCitiesFlow);

        bsm.resetBSMGraph();
    }
}

void Menu::printAffectedCities(const map<int,double>& oldCitiesFlow, map<int,double> newCitiesFlow) {
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
        cout << "     ---" << endl;
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

void Menu::criticalPipes() {
    map<int,vector<pair<Code,Code>>> cityCriticalPipes;  // first - city code , second - vector of pipes

    for (auto v : parser.getCodeGraph().getVertexSet()) {
        for (auto e : v->getAdj()) {
            auto source = v->getInfo();
            auto target = e->getDest()->getInfo();

            if (source.getNumber() == 0 || target.getNumber() == 0) continue;

            vector<pair<Code,Code>> edge;
            edge.emplace_back(source,target);

            bsm.removePipes(edge);
            map<int,double> newCitiesFlow = bsm.getCitiesFlow();

            bsm.resetBSMGraph();

            vector<City> affectedCities;
            for (auto city : newCitiesFlow) {
                int cityCodeNumber = city.first;
                City cityObj = parser.getDataContainer().getCityHashTable().find(cityCodeNumber)->second;
                double cityDemand = cityObj.getDemand();
                double newFlow = city.second;

                if (cityDemand > newFlow) {
                    affectedCities.emplace_back(cityObj);
                }
            }

            for (const auto& affected : affectedCities) {
                cityCriticalPipes[affected.getId()].emplace_back(source,target);
            }
        }
    }

    exportCriticalPipesForEachCity("../output/criticalPipesPerCity.txt", cityCriticalPipes, parser.getDataContainer());
}
