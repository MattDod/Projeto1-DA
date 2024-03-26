#include "Node.h"

// Parameterized constructor
Node::Node(std::string name, double id, std::string code, double demand, double population, NodeType type) : name(name), id(id), code(code), demand(demand), population(population), type(type) {}

// Constructor for water reservoirs
Node::Node(std::string name, std::string municipality, double id, std::string code, double maxDeliveryCapacity, NodeType type)
        : name(name), municipality(municipality), id(id), code(code), maxDeliveryCapacity(maxDeliveryCapacity), type(type) {}

// Constructor for cities
Node::Node(double id, std::string code, NodeType type)
        : id(id), code(code), type(type) {}

// Getter methods
std::string Node::getName() const {
    return name;
}

NodeType Node::getType() const {
    return type;
}

std::string Node::getMunicipality() const{
    return municipality;
}

double Node::getId() const{
    return id;
}

double Node::getMaxDeliveryCapacity() const {
    return maxDeliveryCapacity;
}

double Node::getDemand() const {
    return demand;
}

double Node::getPopulation() const {
    return population;
}

std::string Node::getCode() const {
    return code;
}

Pipeline* Node::addPipe(Node *dest, double capacity, double direction) {
    auto newPipe = new Pipeline(this,dest,  capacity, direction);
    adj.push_back(newPipe);
    return newPipe;
}

bool Node::isVisited() const {
    return visited;
}

void Node::setVisited(bool value) {
    this->visited = value;
}

std::vector<Pipeline *> Node::getAdj() const {
    return adj;
}
