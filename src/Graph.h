#ifndef PROJETODA_GRAPH_H
#define PROJETODA_GRAPH_H

#include <vector>
#include <queue>
#include "Node.h"

class Graph {
private:
public:
    // Method to add a node to the graph
    void addNode(Node *node);
    bool addPipe(std::string &source, std::string &dest, double &capacity, double &direction);
    std::vector<Node *> nodes;
    // Getter method to retrieve all nodes in the graph
    const std::vector<Node *> getNodes() const;
    void copyGraph(const Graph &g);

    Node *findNode(std::string &code) const;
};

#endif // PROJETODA_GRAPH_H
