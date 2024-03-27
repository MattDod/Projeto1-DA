#include <iostream>
#include "System.h"
#include "Menu.h"

//
// Created by kamert on 19-03-2024.
//
using namespace std;

void Menu::start(System system){
    while(true) {
        Graph *copy = new Graph();
        copy->copyGraph(system.getGraph());
        cout << endl << "Menu:" << endl;
        cout << "1: Analyse the maximum amount of water" << endl;
        cout << "2: Analyse what would happen if the network were to change" << endl;
        cout << "Press a number to continue or press 0 to quit" << endl;
        int choice;
        cin >> choice;
        while (0 < choice && choice > 2) {
            cout << "Please select a valid choice." << endl;
            cin >> choice;
        }
        switch (choice) {
            case 0:
                return;
            case 1:
                normalFlowMenu(system, copy);
                break;
            case 2:
                avoidFlowMenu(system, copy);
                break;
            default:
                return;
        }
    }
}

void Menu::normalFlowMenu(System system, Graph *graph){
    cout << endl;
    cout << "1: Choose a specific city" << endl;
    cout << "2: Choose all cities" << endl;
    cout << "3: Check if the cities' needs are met" << endl;
    int option;
    cin >> option;
    system.edmondsKarp(graph);
    switch (option) {
        case 0:
            return;
        case 1: {
            cout << "Please insert the code of the desired city." << endl;
            string code;
            cin >> code;
            Node *chosenNode = graph->findNode(code);
            if (chosenNode == nullptr) {
                cout << "City not found." << endl;
                break;
            }
            system.printFlow(graph, code);
            break;
        }
        case 2: {
            system.printFlow(graph, "all");
            break;
        }
        case 3: {
            system.cityNeeds(graph);
            break;
        }
        default:
            cout << "Invalid option." << endl;
            return;
    }
}

void Menu::avoidFlowMenu(System system, Graph *graph) {
    cout << endl;
    cout << "1: A Water Reservoir were to be out of comission" << endl;
    cout << "2: A Pumping Station were to be taken out of service" << endl;

    int option;
    cin >> option;
    switch (option) {
        case 1: {
            cout << "Please insert the code of the Water Reservoir to be taken out." << endl;
            string code;
            cin >> code;
            Node *chosenNode = graph->findNode(code);
            if (chosenNode == nullptr || chosenNode->getType() != NodeType::WaterReservoir) {
                cout << "Not a valid code." << endl;
                break;
            }
            system.edmondsKarpAvoid(graph, code);
            system.cityNeeds(graph);
            break;
        }
        case 2: {
            cout << "Please insert the code of the Pumping Station to be taken out." << endl;
            string code;
            cin >> code;
            Node *chosenNode = graph->findNode(code);
            if (chosenNode == nullptr || chosenNode->getType() != NodeType::PumpingStation) {
                cout << "Not a valid code." << endl;
                break;
            }
            system.edmondsKarpAvoid(graph, code);
            system.cityNeeds(graph);
            break;
        }

        default:
            cout << "Invalid option." << endl;
            return;
    }
}