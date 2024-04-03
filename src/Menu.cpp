#include "Menu.h"

using namespace std;

string reservoirCSV = "../small-dataSet/Reservoirs_Madeira.csv";
string stationsCSV = "../small-dataSet/Stations_Madeira.csv";
string citiesCSV = "../small-dataSet/Cities_Madeira.csv";
string pipesCSV = "../small-dataSet/Pipes_Madeira.csv";

Menu::Menu() : parser(reservoirCSV, stationsCSV, citiesCSV, pipesCSV), bsm(parser.getCodeGraph(), parser.getDataContainer()){
    menuIndex = {
            makeBold("[0] Print All Data Container"),
            makeBold("[1] Print Specific Data Container"),
            makeBold("[2] Total Max Flow"),
            makeBold("[3] City Flow"),
            makeBold("[4] Print All Cities Flow"),
            makeBold("[5] Print All Cities With Water Deficit"),
            makeBold("[6] Print Each Pipe Flow Difference"),
            makeBold("[7] EXIT")
    };
    bsm.edmondsKarp();
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

int Menu::inputParser(int& choice, string text) {
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
    for (auto e : menuIndex) {
        cout << "   │  " << e << endl;
    }
    cout << "   │" << endl;
}

int Menu::run() {
    while (true) {
        clearScreen();
        printMenu();

        int choice;
        if (inputParser(choice, "Enter your choice: ")) return 1;

        clearScreen();
        switch (choice) {
            case 0:
                printAllDataContainer();
                break;
            case 1:
                if (printSpecificDataContainer()) return 1;
                break;
            case 2:
                getTotalMaxFlow();
                break;
            case 3:
                getCityFlow();
                break;
            case 4:
                printEachCityMaxFlow(bsm.getBSMGraph(), parser.getDataContainer());
                break;
            case 5:
                printCitiesWithWaterFlowDeficit(bsm.getBSMGraph(), parser.getDataContainer());
                break;
            case 6:
                printEachPipeDifference(bsm.getBSMGraph());
                break;
            case 7:
                clearScreen();
                return 0;
        }
        waitPress();
    }
    return 0;

/*
    printHashInfo(dataContainer, Code("C_3"));
    printAllHashInfo(dataContainer);


    for (const auto& v : parser.getCodeGraph().getVertexSet()) {
        for (const auto& e : v->getAdj()) {
            cout << "Origin: " << e->getOrig()->getInfo().getCompleteCode() << endl;
            cout << "Dest: " << e->getDest()->getInfo().getCompleteCode() << endl;
            cout << "Capacity: " << e->getWeight() << endl;
            cout << "Flow: " << e->getFlow() << endl;
            cout << "--------------------------------\n" << endl;
        }
    }



    */
    //printEachCityMaxFlow(bsm.getBSMGraph(), dataContainer);
    //printSpecificCityMaxFlow(bsm.getBSMGraph(), dataContainer, Code("C_1"));
    //printCitiesWithWaterFlowDeficit(bsm.getBSMGraph(), dataContainer);

    // check if original graph is modified by BSM functions
    /*std::stringstream ss;
    for(auto v : parser.getCodeGraph().getVertexSet()) {
        ss.str("");
        bool hasContent = false;
        for (const auto e : v->getAdj())
            if (e->getFlow() != 0) {
                ss << e->getDest()->getInfo().getCompleteCode() << "[Flow: " << e->getFlow() << "]";
                hasContent = true;
            } else continue;
        ss << ")";
        if (hasContent) std::cout << v->getInfo().getCompleteCode() << "->(" << ss.str() << std::endl;
    }*/

    return 0;
}

void Menu::printAllDataContainer() {
    printAllHashInfo(parser.getDataContainer());
}

int Menu::printSpecificDataContainer() {
    vector<string> codeType{
        "[0] Reservoir",
        "[1] Station",
        "[2] City"
    };
    for (auto e : codeType) {
        cout << e << endl;
    }

    int choice;
    if (inputParser(choice, "Enter your choice: ")) return 1;

    int codeNumber;
    if (inputParser(codeNumber, "Enter the ID number (eg. C_9, enter 9): ")) return 1;

    cout << endl;
    switch (choice) {
        case 0:
            printHashInfo(parser.getDataContainer(), Code("R_" + to_string(codeNumber)));
            break;
        case 1:
            printHashInfo(parser.getDataContainer(), Code("PS_" + to_string(codeNumber)));
            break;
        case 2:
            printHashInfo(parser.getDataContainer(), Code("C_" + to_string(codeNumber)));
            break;
        default:
            return 1;
    }

    return 0;
}

void Menu::getTotalMaxFlow() {
    cout << endl;
    cout << makeBold("Total max flow: ") << bsm.getTotalMaxFlow() << endl;
}

void Menu::getCityFlow() {
    int codeNumber;
    if (inputParser(codeNumber, "Enter the City ID number (eg. C_9, enter 9): ")) {
        cout << "ERROR: Couldn't find City" << endl;
    };

    Code cityCode("C_" + to_string(codeNumber));
    cout << makeBold("Flow to City [" + cityCode.getCompleteCode() +"]: ") << bsm.getFlowToCity(cityCode) << endl;
    cout << makeBold("City demand: ") << parser.getDataContainer().getCityHashTable().find(codeNumber)->second.getDemand() << endl;
}
