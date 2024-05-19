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
    /**
     * Displays the main menu
     * Complexity: O(1)
     */
    void mainMenu();

    /**
     * Clears the screen
     * Complexity: O(1)
     */
    static void clearScreen();

    /**
     * Displays the extra graphs menu
     * Complexity: O(1)
     */
    static void extraGraphsMenu();

    /**
     * Displays the real world graphs menu
     * Complexity: O(1)
     */
    static void realWorldGraphsMenu();

    /**
     * Displays the toy graphs menu
     * Complexity: O(1)
     */
    static void toyGraphsMenu();

    /**
     * Displays the algorithms menu
     * Complexity: O(1)
     */
    static void chooseAlgorithm();
};


#endif // DA_ROUTINGALGORITHMS_MENU_H
