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


bool Graph::addPipe(std::string &source, std::string &dest, double &capacity, double &direction) {
    auto v1 = findNode(source);
    auto v2 = findNode(dest);
    if(v1 == nullptr || v2 == nullptr)
        return false;
    v1->addPipe(v2, capacity, direction);
    return true;
}

Node * Graph::findNode(std::string &code) const{
    for (auto v : nodes){
        if(v->getCode() == code){
            return v;
        }
    }
    return nullptr;
}

void Graph::copyGraph(const Graph &g) {
    for(auto v : g.getNodes()) {
        NodeType type = v->getType();
        Node *toAdd;
        switch (type) {
            case NodeType::City: {
                toAdd = new Node(v->getName(), v->getId(), v->getCode(), v->getDemand(), v->getPopulation(), NodeType::City);
                addNode(toAdd);
                break;
            }
            case NodeType::PumpingStation: {
                toAdd = new Node(v->getId(), v->getCode(), NodeType::PumpingStation);
                addNode(toAdd);
                break;
            }
            case NodeType::WaterReservoir: {
                toAdd = new Node(v->getName(), v->getMunicipality(), v->getId(), v->getCode(), v->getMaxDeliveryCapacity(), NodeType::WaterReservoir);
                addNode(toAdd);
                break;
            }
        }
        for(auto pipe : v->getAdj()) {
            toAdd->addPipe(pipe->getTarget(), pipe->getCapacity()+5, pipe->getDirection());
        }
    }
}
