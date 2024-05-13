//
// Created by jpnsantos on 21/03/24.
//

#ifndef DA_ROUTINGALGORITHMS_MENU_H
#define DA_ROUTINGALGORITHMS_MENU_H


#include <iostream>

#include "utils/Dataset.h"

using namespace std;

class Menu {
public:
    void display();

    static void backToMain(); // Add this line
    void mainMenu();

    void clearScreen();

    void wait();

    void backtrackingAlgorithm();

    void triangularApproximationHeuristic();

    void nearestNeighborHeuristic();

    void christofidesHeuristic();
};


#endif // DA_ROUTINGALGORITHMS_MENU_H
