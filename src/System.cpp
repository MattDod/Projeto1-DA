//
// Created by kamert on 19-03-2024.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "System.h"

System::System(){
   readCities("../data/Cities.csv");
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
            Node nodecity(city, id, code, demand, population, NodeType::City);
            cout << city << code << id << demand << population;
            g.addNode(&nodecity);


        }
    }
    file.close();
}


/**void System::readStations(const std::string &filename) {
    ifstream file(filename);
    string line;
    std::getline(file, line); // Ignora a primeira linha (cabeçalho)

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return;
    }
    while (getline(file, line)) {
        istringstream s(line);
        std::string code;
        double id;
        char comma;
        if (s >> id >> comma &&
            getline(s, code, ',')){
            Node nodecity(city, id, code, demand, population, NodeType::City);
            cout << city << code << id << demand << population;
            g.addNode(&nodecity);


        }
    }
    file.close();
} */