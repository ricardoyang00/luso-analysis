#include "Menu.h"

using namespace std;

string reservoirCSV = "../large-dataSet/Reservoir.csv";
string stationsCSV = "../large-dataSet/Stations.csv";
string citiesCSV = "../large-dataSet/Cities.csv";
string pipesCSV = "../large-dataSet/Pipes.csv";

Menu::Menu() : parser(reservoirCSV, stationsCSV, citiesCSV, pipesCSV){
    menuIndex = {
            makeBold("[0] Print all Data Container"),
            makeBold("[1] Print Specific Data Container"),
            makeBold("[2] Total Max Flow"),
            makeBold("[3] EXIT")
    };
}

void Menu::clearScreen() {
    system("clear || cls");
}

int Menu::intputParser(int& choice, string text) {
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
        if (intputParser(choice, "Enter your choice: ")) return 1;

        clearScreen();
        switch (choice) {
            case 0:
                if (printAllDataContainer()) return 1;
                break;
            case 1:
                if (printSpecificDataContainer()) return 1;
                break;
            case 3:
                clearScreen();
                return 0;
        }
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

    BasicServiceMetrics bsm(parser.getCodeGraph(), dataContainer);

    bsm.edmondsKarp();

    cout << "Total max flow: " << bsm.getTotalMaxFlow() << endl;

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

int Menu::printAllDataContainer() {
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
    if (intputParser(choice, "Enter your choice: ")) return 1;

    int codeNumber;
    if (intputParser(codeNumber, "Enter the ID number (eg. C_9, enter 9): ")) return 1;

    switch (choice) {
        case 0:
            printHashInfo(parser.getDataContainer(), Code("R_" + to_string(codeNumber)));
            break;
        case 1:
            printHashInfo(parser.getDataContainer(), Code("S_" + to_string(codeNumber)));
            break;
        case 2:
            printHashInfo(parser.getDataContainer(), Code("C_" + to_string(codeNumber)));
            break;
        default:
            return 1;
    }

    return 0;

}