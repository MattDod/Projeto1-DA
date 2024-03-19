//
// Created by kamert on 19-03-2024.
//

#ifndef PROJETODA_SYSTEM_H
#define PROJETODA_SYSTEM_H

#include "Graph.h"

using namespace std;
class System{
private:
    Graph g;
public:
    System();
    void readCities(const string &filename);
    void readPipes(const string &filename);
    void readReservoir(const string &filename);
    void readStations(const string &filename);

    void showgraph();

};
#endif //PROJETODA_SYSTEM_H
