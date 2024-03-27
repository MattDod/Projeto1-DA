#include <iostream>
#include "System.h"
#include "Menu.h"

//
// Created by kamert on 19-03-2024.
//
using namespace std;
void Menu::start(System system){
    while(true){
        cout << endl << "Menu:" << endl;
        cout << "Press a number to continue or press 0 to quit" << endl;
        int choice;
        cin >> choice;
        if(choice == 1){
            system.edmondsKarp();
        }
        else
        if(choice == 0){
            break;
        }
    }
}