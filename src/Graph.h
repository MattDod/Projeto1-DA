#ifndef PROJETODA_GRAPH_H
#define PROJETODA_GRAPH_H

#include <vector>
#include "Node.h"

class Graph {
private:
    std::vector<Node> nodes;

public:
    // Method to add a node to the graph
    void addNode(const Node node);

    // Getter method to retrieve all nodes in the graph
     const std::vector<Node> getNodes() const;
};

#endif // PROJETODA_GRAPH_H
