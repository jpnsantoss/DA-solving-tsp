
#include "Menu.h"

void Menu::mainMenu() {
    clearScreen();
    cout << "**********************************************\n"
         << "*                                            *\n"
         << "*  Routing Algorithms: Select an Algorithm   *\n"
         << "*                                            *\n"
         << "*     1) Backtracking Algorithm              *\n"
         << "*     2) Triangular Approximation Heuristic  *\n"
         << "*     3) Nearest Neighbor Heuristic          *\n"
         << "*     4) Christofides Heuristic              *\n"
         << "*     0) EXIT                                *\n"
         << "*                                            *\n"
         << "**********************************************\n"
         << "Option: ";
    int option;
    while (!(cin >> option) || option < 0 || option > 4) {
        cout << "Invalid option. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    switch (option) {
        case 1: {
            backtrackingAlgorithm();
            break;
        }
        case 2: {
            triangularApproximationHeuristic();
            break;
        }
        case 3: {
            nearestNeighborHeuristic();
            break;
        }
        case 4: {
            christofidesHeuristic();
            break;
        }
        case 0:
            exit(0);
    }
}
void Menu::backtrackingAlgorithm() {
    clearScreen();
    cout << "**********************************************\n"
         << "*                                            *\n"
         << "*     Routing Algorithms: Backtracking       *\n"
         << "*     (Toy Graphs)                           *\n"
         << "*                                            *\n"
         << "*     1) RUN                                 *\n"
         << "*     0) BACK                                *\n"
         << "*                                            *\n"
         << "**********************************************\n"
         << "Option: ";
    int option;
    while (!(cin >> option) || option < 0 || option > 5) {
        cout << "Invalid option. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    switch (option) {
        case 1: {
            cout << "Running backtracking algorithm..." << endl;
            break;
        }
        case 0: {
            mainMenu();
            break;
        }
    }
}

void Menu::triangularApproximationHeuristic() {
    clearScreen();
    cout << "**********************************************\n"
         << "*                                            *\n"
         << "*     Routing Algorithms: Backtracking       *\n"
         << "*     (Toy Graphs)                           *\n"
         << "*                                            *\n"
         << "*     1) Run for Extra Graphs                *\n"
         << "*     2) Run for Real World Graphs           *\n"
         << "*     0) BACK                                *\n"
         << "*                                            *\n"
         << "**********************************************\n"
         << "Option: ";
    int option;
    while (!(cin >> option) || option < 0 || option > 5) {
        cout << "Invalid option. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    switch (option) {
        case 1: {
            cout << "Running Triangular Approximation Heuristic for Extra Graphs..." << endl;
            break;
        }
        case 2: {
            cout << "Running Triangular Approximation Heuristic for Real World Graphs..." << endl;
            break;
        }
        case 0: {
            mainMenu();
            break;
        }
    }
}

void Menu::nearestNeighborHeuristic() {
    clearScreen();
    cout << "**********************************************\n"
         << "*                                            *\n"
         << "*     Routing Algorithms: Nearest Neighbor    *\n"
         << "*     (Toy Graphs)                           *\n"
         << "*                                            *\n"
         << "*     1) Run for Extra Graphs                *\n"
         << "*     2) Run for Real World Graphs           *\n"
         << "*     0) BACK                                *\n"
         << "*                                            *\n"
         << "**********************************************\n"
         << "Option: ";
    int option;
    while (!(cin >> option) || option < 0 || option > 5) {
        cout << "Invalid option. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    switch (option) {
        case 1: {
            cout << "Running Nearest Neighbor Heuristic for Extra Graphs..." << endl;
            break;
        }
        case 2: {
            cout << "Running Nearest Neighbor Heuristic for Real World Graphs..." << endl;
            break;
        }
        case 0: {
            mainMenu();
            break;
        }
    }
}

void Menu::christofidesHeuristic() {
    clearScreen();
    cout << "**********************************************\n"
         << "*                                            *\n"
         << "*     Routing Algorithms: Christofides       *\n"
         << "*     (Toy Graphs)                           *\n"
         << "*                                            *\n"
         << "*     1) Run for Extra Graphs                *\n"
         << "*     2) Run for Real World Graphs           *\n"
         << "*     0) BACK                                *\n"
         << "*                                            *\n"
         << "**********************************************\n"
         << "Option: ";
    int option;
    while (!(cin >> option) || option < 0 || option > 5) {
        cout << "Invalid option. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    switch (option) {
        case 1: {
            cout << "Running Christofides Heuristic for Extra Graphs..." << endl;
            break;
        }
        case 2: {
            cout << "Running Christofides Heuristic for Real World Graphs..." << endl;
            break;
        }
        case 0: {
            mainMenu();
            break;
        }
    }
}

void Menu::clearScreen() {
    for (int i = 0; i < 50; i++) {
        std::cout << std::endl;
    }
    system("clear");
}
