#include "Graph.h"
#include "Node.h"

// Method to add a node to the graph
void Graph::addNode(Node *node) {
    nodes.push_back(node);
}

// Getter method to retrieve all nodes in the graph
const std::vector<Node *> Graph::getNodes() const {
    return nodes;
}


bool Graph::addPipe(std::string source, std::string dest, double capacity, double direction) {
    auto v1 = findNode(source);
    auto v2 = findNode(dest);
    if(v1 == nullptr || v1 == nullptr)
        return false;
    v1->addPipe(v2, capacity, direction);
}

Node * Graph::findNode(std::string code) const{
    for (auto v : nodes){
        if(v->getCode() == code){
            return v;
        }
    }
    return nullptr;
}
