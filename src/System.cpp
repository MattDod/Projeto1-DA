//
// Created by kamert on 19-03-2024.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "System.h"

System::System(){
   readCities("../small_data/Cities_Madeira.csv");
   readStations("../small_data/Stations_Madeira.csv");
   readReservoir("../small_data/Reservoirs_Madeira.csv");
   readPipes("../small_data/Pipes_Madeira.csv");
    for(auto v : g.nodes){
        cout<< v->getCode() << endl;
        for(auto e : v->adj){
            cout << e->getCapacity() <<" "<< e->getTarget()->getCode() <<" "<< e->getDirection() << endl;
        }
    }
}
void System::readCities(const std::string &filename) {
    ifstream file(filename);
    string line;
    std::getline(file, line); // Ignora a primeira linha (cabeçalho)

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return;
    }
    while (getline(file, line)) {
        istringstream s(line);
        std::string city, code, id, demand, population;
        getline(s, city, ',');
        getline(s, id, ',');
        getline(s, code, ',');
        getline(s, demand, ',');
        getline(s, population, '\r');
        double id2 = stod(id);
        double demand2 = stod(demand);
        double population2 = stod(population);
        Node *nodecity = new Node(city, id2, code, demand2, population2, NodeType::City);
        g.addNode(nodecity);



    }
    file.close();
}


void System::readStations(const std::string &filename) {
    ifstream file2(filename);
    string line;
    std::getline(file2, line); // Ignora a primeira linha (cabeçalho)

    if (!file2.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return;
    }
    while (getline(file2, line)) {
        istringstream s(line);
        std::string code, id;
        getline(s, id, ',');
        getline(s, code, '\r');
        double id2 = stod(id);
        Node *nodecity = new Node(id2, code, NodeType::PumpingStation);
        g.addNode(nodecity);


        }
    file2.close();
}

//Reservoir,Municipality,Id,Code,Maximum Delivery (m3/sec)

void System::readReservoir(const std::string &filename){
    ifstream file3(filename);
    string line;
    std::getline(file3, line); // Ignora a primeira linha (cabeçalho)

    if (!file3.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return;
    }
    while (getline(file3, line)) {
        istringstream s(line);
        std::string reservoir, municipality, id, code, maxDelivery;
        getline(s, reservoir, ',');
        getline(s, municipality, ',');
        getline(s, id, ',');
        getline(s, code, ',');
        getline(s, maxDelivery, '\r');
        double id2 = stod(id);
        double maxDelivery2 = stod(maxDelivery);
        Node *nodecity = new Node(reservoir, municipality, id2, code, maxDelivery2, NodeType::WaterReservoir);
        g.addNode(nodecity);
    }
    file3.close();
}

//Service_Point_A,Service_Point_B,Capacity,Direction
void System::readPipes(const std::string &filename) {
    ifstream file4(filename);
    string line;
    std::getline(file4, line); // Ignora a primeira linha (cabeçalho)
    if (!file4.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return;
    }
    while (getline(file4, line)) {
        istringstream s(line);
        string source, target, capacity, direction;
        getline(s, source, ',');
        getline(s, target, ',');
        getline(s, capacity, ',');
        getline(s, direction, '\r');
        double capacity2 = stod(capacity);
        double direction2 = stod(direction);
        auto v1 = g.findNode(source);
        auto v2 = g.findNode(target);
        v1->addPipe(v2, capacity2, direction2);
        //Handling the case where the pipeline is bidirectional
        if(direction2 == 0){
            v2->addPipe(v1, capacity2, direction2);
        }
    }
    file4.close();
}