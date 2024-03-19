#include "Graph.h"
#include "Node.h"

// Method to add a node to the graph
void Graph::addNode(const Node node) {
    nodes.push_back(node);
}

// Getter method to retrieve all nodes in the graph
const std::vector<Node> Graph::getNodes() const {
    return nodes;
}
