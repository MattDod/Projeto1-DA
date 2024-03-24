#include "Node.h"

// Parameterized constructor
Node::Node(std::string name, double id, std::string code, double demand, double population, NodeType type) : name(name), id(id), code(code), demand(demand), population(population), type(type) {}

// Constructor for water reservoirs
Node::Node(std::string name, std::string municipality, double id, std::string code, double maxDeliveryCapacity)
        : name(name), municipality(municipality), id(id), code(code), maxDeliveryCapacity(maxDeliveryCapacity) {}

// Constructor for cities
Node::Node(double id, std::string code)
        : id(id), code(code) {}

// Getter methods
std::string Node::getName() const {
    return name;
}

NodeType Node::getType() const {
    return type;
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
