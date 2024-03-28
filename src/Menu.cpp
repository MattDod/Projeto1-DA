#include <iostream>
#include <iomanip>
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
        cout << endl << "Menu:" << endl << endl;
        cout << "1: Analyse the normal flow of water." << endl;
        cout << "2: Analyse what would happen if the network were to change." << endl;
        cout << "0: Quit" << endl;
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
    cout << endl << "Analyse the normal flow of water." << endl << endl;
    cout << "1: Of a specific city" << endl;
    cout << "2: Of all cities" << endl;
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
    cout << endl << "Analyse what would happen if:" << endl << endl;
    cout << "1: A Water Reservoir were to be out of commission" << endl;
    cout << "2: A Pumping Station were to be taken out of service" << endl;
    cout << "3: A Pipeline were to rupture." << endl;

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
            system.edmondsKarpAvoidNode(graph, code);
            system.cityNeeds(graph);
            break;
        }
        case 2: {
            system.edmondsKarp(graph);
            vector<pair<Node*, double>> originalFlowInfo = system.cityFlowInfo(graph);
            for(auto node : graph->getNodes()){
                if(node->getType() == NodeType::PumpingStation){
                    cout << endl << "Pumping Station: " << node->getCode() << endl;
                    Graph *copy = new Graph();
                    copy->copyGraph(system.getGraph());
                    string code = node->getCode();
                    system.edmondsKarpAvoidNode(copy, code);
                    vector<pair<Node*, double>> newFlowInfo = system.cityFlowInfo(copy);
                    int size = originalFlowInfo.size();
                    bool header=false;
                    bool found = false;
                    for(int i = 0; i < size; i++){
                        if(originalFlowInfo[i].second != newFlowInfo[i].second && !header){
                            header = true;
                            found = true;
                            cout << left << setw(20) << "City" << setw(15) << "Original flow" << setw(10) << "New flow" << setw(10) << "Difference" << endl;
                            cout << left << setw(20) << originalFlowInfo[i].first->getName() << setw(15) << originalFlowInfo[i].second << setw(10) << setw(10) << newFlowInfo[i].second << newFlowInfo[i].second - originalFlowInfo[i].second << endl;
                        }
                        else if (originalFlowInfo[i].second != newFlowInfo[i].second){
                            cout << left << setw(20) << originalFlowInfo[i].first->getName() << setw(15) << originalFlowInfo[i].second << setw(10) << setw(10) << newFlowInfo[i].second << newFlowInfo[i].second - originalFlowInfo[i].second << endl;
                        }
                    }
                    if(!found){
                        cout << "There aren't any affected cities" << endl;
                    }
                    delete copy;
                }
            }
            break;
        }

        case 3: {
            system.edmondsKarp(graph);
            vector<pair<Node*, double>> originalFlowInfo = system.cityFlowInfo(graph);
            for(auto node : graph->getNodes()){
                for(auto pipe : node->getAdj()){
                    if(pipe->getSourceNode()->getType() == NodeType::SuperSource ||  pipe->getTarget()->getType() == NodeType::SuperSink){
                        continue;
                    }
                    cout << endl << "Pipeline: " << pipe->getSourceNode()->getCode() << "->" << pipe->getTarget()->getCode() << endl;
                    Graph *copy = new Graph();
                    copy->copyGraph(system.getGraph());
                    string code = pipe->getTarget()->getCode();
                    system.edmondsKarpAvoidPipeline(copy, pipe);
                    vector<pair<Node*, double>> newFlowInfo = system.cityFlowInfo(copy);
                    int size = originalFlowInfo.size();
                    bool header=false;
                    bool found = false;
                    for(int i = 0; i < size; i++){
                        if(originalFlowInfo[i].second != newFlowInfo[i].second && !header){
                            header = true;
                            found = true;
                            cout << left << setw(20) << "City" << setw(15) << "Original flow" << setw(10) << "New flow" << setw(10) << "Difference" << endl;
                            cout << left << setw(20) << originalFlowInfo[i].first->getName() << setw(15) << originalFlowInfo[i].second << setw(10) << setw(10) << newFlowInfo[i].second << newFlowInfo[i].second - originalFlowInfo[i].second << endl;
                        }
                        else if (originalFlowInfo[i].second != newFlowInfo[i].second){
                            cout << left << setw(20) << originalFlowInfo[i].first->getName() << setw(15) << originalFlowInfo[i].second << setw(10) << setw(10) << newFlowInfo[i].second << newFlowInfo[i].second - originalFlowInfo[i].second << endl;
                        }
                    }
                    if(!found){
                        cout << "There aren't any affected cities" << endl;
                    }
                    delete copy;
                }
            }
            break;
        }

        default:
            cout << "Invalid option." << endl;
            return;
    }
}