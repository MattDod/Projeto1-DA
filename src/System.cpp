//
// Created by kamert on 19-03-2024.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "System.h"

System::System(){
   readCities("../data/Cities.csv");
   readStations("../data/Stations.csv");
   readReservoir("../data/Reservoir.csv");
   readPipes("../data/Pipes.csv");

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
        std::string city, code;
        double id, demand, population;
        char comma;
        if (getline(s, city, ',') && s >> id >> comma &&
            getline(s, code, ',') && s >> demand >> comma && s >> population) {
            Node *nodecity = new Node(city, id, code, demand, population, NodeType::City);
            g.addNode(nodecity);


        }
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
        std::string code;
        double id;
        char comma;
        if (s >> id >> comma &&
            getline(s, code, ',')){
            Node *nodecity = new Node(id, code, NodeType::PumpingStation);
            g.addNode(nodecity);


        }
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
        std::string reservoir, municipality, code;
        double id, maxDelivery;
        char comma;
        if (getline(s, reservoir, ',') && getline(s, municipality, ',') &&
            s >> id >> comma && getline(s, code, ',') && s >> maxDelivery) {
            Node *nodecity = new Node(reservoir, municipality, id, code, maxDelivery, NodeType::WaterReservoir);
            g.addNode(nodecity);



        }
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
        string source, target;
        double capacity, direction;
        char comma;
        if (getline(s,source, ',') && getline(s, target, ',')
            && s >> capacity >> comma && s >> direction) {
            auto v1 = g.findNode(source);
            auto v2 = g.findNode(target);
            v1->addPipe(v2, capacity, direction);

        }

    }
    file4.close();
}