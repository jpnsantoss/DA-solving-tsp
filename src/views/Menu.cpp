
#include "Menu.h"

void Menu::mainMenu() {
    clearScreen();
    cout << "*****************************************************\n"
         << "*                                                   *\n"
         << "*  Routing Algorithms: Choose a Type of Graph       *\n"
         << "*                                                   *\n"
         << "*     1) Toy Graphs                                 *\n"
         << "*     2) Extra Fully Connected Graphs               *\n"
         << "*     3) Real World Graphs                          *\n"
         << "*                                                   *\n"
         << "*     0) EXIT                                       *\n"
         << "*                                                   *\n"
         << "*****************************************************\n"
         << "Option: ";

    int option;
    while (!(cin >> option) || option < 0 || option > 3) {
        cout << "Invalid option. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (option) {
        case 1: {
            toyGraphsMenu();
            break;
        }
        case 2: {
            extraGraphsMenu();
            break;
        }
        case 3: {
            realWorldGraphsMenu();
            break;
        }
        case 0:
            exit(0);
        default:
            break;
    }
}

void Menu::clearScreen() {
    for (int i = 0; i < 50; i++) {
        std::cout << std::endl;
    }
    system("clear");
}

void Menu::extraGraphsMenu() {
    clearScreen();
    cout << "***************************************************\n"
         << "*                                                 *\n"
         << "*     Choose Number of Nodes in the Graph:        *\n"
         << "*                                                 *\n"
         << "*     1) 25 Nodes                                 *\n"
         << "*     2) 50 Nodes                                 *\n"
         << "*     3) 75 Nodes                                 *\n"
         << "*     4) 100 Nodes                                *\n"
         << "*     5) 200 Nodes                                *\n"
         << "*     6) 300 Nodes                                *\n"
         << "*     7) 400 Nodes                                *\n"
         << "*     8) 500 Nodes                                *\n"
         << "*     9) 600 Nodes                                *\n"
         << "*     10) 700 Nodes                               *\n"
         << "*     11) 800 Nodes                               *\n"
         << "*     12) 900 Nodes                               *\n"
         << "*                                                 *\n"
         << "*     0) BACK                                     *\n"
         << "*                                                 *\n"
         << "***************************************************\n"
         << "Option: ";
    int option;
    while (!(cin >> option) || option < 0 || option > 12) {
        cout << "Invalid option. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch(option) {
        case 1:
            Dataset::getInstance()->loadGraph("data/Extra_Fully_Connected_Graphs/edges_25.csv");
            chooseAlgorithm();
            break;
        case 2:
            Dataset::getInstance()->loadGraph("data/Extra_Fully_Connected_Graphs/edges_50.csv");
            chooseAlgorithm();
            break;
        case 3:
            Dataset::getInstance()->loadGraph("data/Extra_Fully_Connected_Graphs/edges_75.csv");
            chooseAlgorithm();
            break;
        case 4:
            Dataset::getInstance()->loadGraph("data/Extra_Fully_Connected_Graphs/edges_100.csv");
            chooseAlgorithm();
            break;
        case 5:
            Dataset::getInstance()->loadGraph("data/Extra_Fully_Connected_Graphs/edges_200.csv");
            chooseAlgorithm();
            break;
        case 6:
            Dataset::getInstance()->loadGraph("data/Extra_Fully_Connected_Graphs/edges_300.csv");
            chooseAlgorithm();
            break;
        case 7:
            Dataset::getInstance()->loadGraph("data/Extra_Fully_Connected_Graphs/edges_400.csv");
            chooseAlgorithm();
            break;
        case 8:
            Dataset::getInstance()->loadGraph("data/Extra_Fully_Connected_Graphs/edges_500.csv");
            chooseAlgorithm();
            break;
        case 9:
            Dataset::getInstance()->loadGraph("data/Extra_Fully_Connected_Graphs/edges_600.csv");
            chooseAlgorithm();
            break;
        case 10:
            Dataset::getInstance()->loadGraph("data/Extra_Fully_Connected_Graphs/edges_700.csv");
            chooseAlgorithm();
            break;
        case 11:
            Dataset::getInstance()->loadGraph("data/Extra_Fully_Connected_Graphs/edges_800.csv");
            chooseAlgorithm();
            break;
        case 12:
            Dataset::getInstance()->loadGraph("data/Extra_Fully_Connected_Graphs/edges_900.csv");
            chooseAlgorithm();
            break;
        default:
            break;
    }
}

void Menu::realWorldGraphsMenu() {
    clearScreen();
    cout << "**********************************************\n"
         << "*                                            *\n"
         << "*     Choose a Real World Graph:             *\n"
         << "*                                            *\n"
         << "*     1)Graph 1                              *\n"
         << "*     2)Graph 2                              *\n"
         << "*     3)Graph 3                              *\n"
         << "*                                            *\n"
         << "*     0) BACK                                *\n"
         << "*                                            *\n"
         << "**********************************************\n"
         << "Option: ";
    int option;
    while (!(cin >> option) || option < 0 || option > 3) {
        cout << "Invalid option. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    switch(option) {
        case 1:
            Dataset::getInstance()->loadRealWorldGraph("data/Real_World_Graphs/graph1/nodes.csv", "data/Real_World_Graphs/graph1/edges.csv");
            chooseAlgorithm();
            break;
        case 2:
            Dataset::getInstance()->loadRealWorldGraph("data/Real_World_Graphs/graph2/nodes.csv", "data/Real_World_Graphs/graph2/edges.csv");
            chooseAlgorithm();
            break;
        case 3:
            Dataset::getInstance()->loadRealWorldGraph("data/Real_World_Graphs/graph3/nodes.csv", "data/Real_World_Graphs/graph3/edges.csv");
            chooseAlgorithm();
            break;
        default:
            break;
    }
}

void Menu::toyGraphsMenu() {
    clearScreen();
    cout << "**********************************************\n"
         << "*                                            *\n"
         << "*     Choose a Toy Graph:                    *\n"
         << "*                                            *\n"
         << "*     1)Shipping                             *\n"
         << "*     2)Stadiums                             *\n"
         << "*     3)Tourism                              *\n"
         << "*                                            *\n"
         << "*     0) BACK                                *\n"
         << "*                                            *\n"
         << "**********************************************\n"
         << "Option: ";
    int option;
    while (!(cin >> option) || option < 0 || option > 3) {
        cout << "Invalid option. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    switch (option) {
        case 1:
            Dataset::getInstance()->loadGraph("data/Toy_Graphs/shipping.csv");
            chooseAlgorithm();
            break;
        case 2:
            Dataset::getInstance()->loadGraph("data/Toy_Graphs/stadiums.csv");
            chooseAlgorithm();
            break;
        case 3:
            Dataset::getInstance()->loadGraph("data/Toy_Graphs/tourism.csv");
            chooseAlgorithm();
            break;
        default:
            break;
    }
}

void Menu::chooseAlgorithm() {
    clearScreen();
    cout << "***************************************************\n"
         << "*                                                 *\n"
         << "*     Choose an Algorithm:                        *\n"
         << "*                                                 *\n"
         << "*     1)Backtracking Algorithm                    *\n"
         << "*     2)Triangular Approximation Heuristic        *\n"
         << "*     3)Nearest Neighbour Heuristic               *\n"
         << "*     4)Christofides Heuristic                    *\n"
         << "*                                                 *\n"
         << "*     0) BACK                                     *\n"
         << "*                                                 *\n"
         << "***************************************************\n"
         << "Option: ";
    int option;
    while (!(cin >> option) || option < 0 || option > 4) {
        cout << "Invalid option. Please try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    vector<int>path;
    double distance;
    clock_t start, end;
    switch(option) {
        case 1:
            path.resize(Dataset::getInstance()->getGraph().getVertexSet().size());
            start = clock();
            distance = Dataset::getInstance()->getGraph().tspBacktracking(path);
            end = clock();
            break;
        case 2:
            path.resize(Dataset::getInstance()->getGraph().getVertexSet().size());
            start = clock();
            distance = Dataset::getInstance()->getGraph().tspTriangularApproximation(path);
            end = clock();

            break;
        case 3:
            start = clock();
            distance = Dataset::getInstance()->getGraph().tspNearestNeighbour(path);
            end = clock();
            break;
        case 4:
            //distance = Dataset::getInstance()->getGraph().tspChristofides();
            break;
        default:
            break;
    }

    cout << "Distance: " << distance << endl;
    cout << "Path: ";

    for(auto v : path) {
        cout << v << " ";
    }

    cout << endl << endl;

    cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    cout << endl << endl;
    cout << "Press 1 to return to the main menu or 0 to exit." << endl;
    int lastChoice;
    cin >> lastChoice;

    if (lastChoice == 0) {
        exit(0);
    }
    else {
        Dataset::getInstance()->getGraph().clearGraph();
        Menu().mainMenu();
    }
}