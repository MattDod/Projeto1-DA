#ifndef PROJETODA_SYSTEM_H
#define PROJETODA_SYSTEM_H

#include "Graph.h"

using namespace std;
class System{
private:
    Graph g;
public:
    Graph getGraph() const;
    System();
    void readCities(const string &filename);
    void readPipes(const string &filename);
    void readReservoir(const string &filename);
    void readStations(const string &filename);

    //Normal Edmonds-Karp algorithm functions
    void edmondsKarp(Graph *copy);
    bool findAugmentingPath(Graph *graph, Node *source, Node *sink);
    double findBottleneckCapacity(Node *source, Node *sink);
    void updateResidualGraph(Node *source, Node *sink, double bottleneck);
    void printFlow(Graph *graph, string choiceCode);
    void cityNeeds(Graph *graph);

    //Special Edmonds-Karp algorithm functions
    void edmondsKarpAvoid(Graph *copy, string avoid);
    bool findAugmentingPathAvoid(Graph *graph, Node *source, Node *sink, string avoid);

};
#endif //PROJETODA_SYSTEM_H
