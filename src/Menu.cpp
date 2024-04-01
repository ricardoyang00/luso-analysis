#include "Menu.h"

using namespace std;
string reservoirCSV = "../large-dataSet/Reservoir.csv";
string stationsCSV = "../large-dataSet/Stations.csv";
string citiesCSV = "../large-dataSet/Cities.csv";
string pipesCSV = "../large-dataSet/Pipes.csv";

Menu::Menu() : parser(reservoirCSV, stationsCSV, citiesCSV, pipesCSV){
    menuIndex = {
            makeBold("[0] Print all Hash Tables"),
            makeBold("[1] Print Specific Hash Table"),
            makeBold("[2] Total Max Flow"),
            makeBold("[3] EXIT")
    };
}

void Menu::clearScreen() {
    system("clear || cls");
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
        cout << "\nEnter your choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;  // Invalid choice (not an integer)
        }

        switch (choice) {
            case 3:
                clearScreen();
                return 0;
        }
    }
    return 0;
    /*std::string reservoirCSV = "../small-dataSet/Reservoirs_Madeira.csv";
   std::string stationsCSV = "../small-dataSet/Stations_Madeira.csv";
   std::string citiesCSV = "../small-dataSet/Cities_Madeira.csv";
   std::string pipesCSV = "../small-dataSet/Pipes_Madeira.csv";*/





    printHashInfo(dataContainer, Code("C_3"));
    printAllHashInfo(dataContainer);

    /*
    for (const auto& v : parser.getCodeGraph().getVertexSet()) {
        for (const auto& e : v->getAdj()) {
            cout << "Origin: " << e->getOrig()->getInfo().getCompleteCode() << endl;
            cout << "Dest: " << e->getDest()->getInfo().getCompleteCode() << endl;
            cout << "Capacity: " << e->getWeight() << endl;
            cout << "Flow: " << e->getFlow() << endl;
            cout << "--------------------------------\n" << endl;
        }
    }*/

    BasicServiceMetrics bsm(parser.getCodeGraph(), dataContainer);

    bsm.edmondsKarp();

    cout << "Total max flow: " << bsm.getTotalMaxFlow() << endl;
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