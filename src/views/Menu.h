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
    void mainMenu();

    static void clearScreen();

    static void extraGraphsMenu();

    static void realWorldGraphsMenu();

    static void toyGraphsMenu();

    static void chooseAlgorithm();
};


#endif // DA_ROUTINGALGORITHMS_MENU_H
