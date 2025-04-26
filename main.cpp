/* Citation and Sources...
Final Project Milestone 3
Module: Menu
Filename: Menu.cpp
Version 1.0
Author: April Roxelle Garcia
Revision History
-----------------------------------------------------------
Date		Reason				Milestone
2025/3/8	File created			1
2025/3/16   File created			2
2025/3/23	File Created			3
2025/3/30	File Created			4
2025/4/10	File Created			5
-----------------------------------------------------------
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Menu.h"
#include "Ordering.h"
using namespace seneca;
using namespace std;

int main() {
    Ordering order("drinks.csv", "foods.csv");
    if (!order) {
        cout << "Failed to open data files or the data files are corrupted!";
        exit(1);
    }

    unsigned int menuSelect = 0;
    unsigned int orderSelect = 0;
    unsigned int saveSelect = 0;

    bool exitProgram = false;
    bool contOrder = true;

    Menu mainMenu("Seneca Restaurant ", "End Program");
    mainMenu << "Order" << "Print Bill" << "Start a New Bill" << "List Foods" << "List Drinks";

    Menu subMenu("Order Menu", "Back to main menu", 1);
    subMenu << "Food" << "Drink";

    while (!exitProgram) {
        menuSelect = mainMenu.select();

        if (menuSelect == 1) {  
            contOrder = true;
            while (contOrder) {
                orderSelect = subMenu.select();

                if (orderSelect == 1) {
                    order.orderFood();
                }
                else if (orderSelect == 2) {
                    order.orderDrink();
                }
                else if (orderSelect == 0) {
                    contOrder = false;  
                }
            }
        }
        else if (menuSelect == 2) { 
            order.printBill(cout);
        }
        else if (menuSelect == 3) {  
            order.resetBill();
        }
        else if (menuSelect == 4) { 
            order.listFoods();
        }
        else if (menuSelect == 5) { 
            order.listDrinks();
        }
        else if (menuSelect == 0) {
            if (order.hasUnsavedBill()) {
                Menu confirm("You have bills that are not saved, are you sue you want to exit?", "No");
                confirm << "Yes";
                saveSelect = confirm.select();

                if (saveSelect == 1) {
                    exitProgram = true;  
                }
               
            }
            else {
                exitProgram = true; 
            }
        }
    }

    return 0;
}
