#include "Menu.h"

using namespace std;

int main() {
    Menu menu;
    if (menu.run()) {
        cout << "ERROR: COULDN'T RUN MENU INTERFACE" << endl;
        return 1;
    }

    cout << "BYE BYE :)" << endl;
    return 0;
}
