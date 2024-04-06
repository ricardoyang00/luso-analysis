#include "Menu.h"

using namespace std;

int main() {
    string reservoirCSV, stationsCSV, citiesCSV, pipesCSV;
    bool dataSetChosen = false;
    while (!dataSetChosen) {
        cout << "\n";
        cout << makeBold("Choose dataset:") << endl;
        cout << "1. Portugal Continental (large dataset)" << endl;
        cout << "2. Madeira (small dataset)" << endl;
        cout << "\n";
        cout << "Enter your choice (1 or 2): ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            reservoirCSV = "../data/large-dataSet/Reservoirs.csv";
            stationsCSV = "../data/large-dataSet/Stations.csv";
            citiesCSV = "../data/large-dataSet/Cities.csv";
            pipesCSV = "../data/large-dataSet/Pipes.csv";
            dataSetChosen = true;
        } else if (choice == 2) {
            reservoirCSV = "../data/small-dataSet/Reservoirs_Madeira.csv";
            stationsCSV = "../data/small-dataSet/Stations_Madeira.csv";
            citiesCSV = "../data/small-dataSet/Cities_Madeira.csv";
            pipesCSV = "../data/small-dataSet/Pipes_Madeira.csv";
            dataSetChosen = true;
        } else {
            cout << "INVALID CHOICE PLEASE TRY AGAIN" << endl;
            system("clear || cls");
        }
    }

    Menu menu(reservoirCSV, stationsCSV, citiesCSV, pipesCSV);
    if (menu.run()) {
        cout << "ERROR: COULDN'T RUN MENU INTERFACE" << endl;
        return 1;
    }

    cout << "BYE BYE :)" << endl;
    return 0;
}
