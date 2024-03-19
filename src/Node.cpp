#include "Node.h"

// Default constructor
Node::Node() : name(""), type(NodeType::WaterReservoir), maxDeliveryCapacity(0), demand(0), population(0), currentFlow(0) {}

// Parameterized constructor
Node::Node(std::string name, NodeType type) : name(name), type(type), maxDeliveryCapacity(0), demand(0), population(0), currentFlow(0) {}

// Constructor for water reservoirs
Node::Node(std::string name, NodeType type, double maxDeliveryCapacity)
        : name(name), type(type), maxDeliveryCapacity(maxDeliveryCapacity), demand(0), population(0), currentFlow(0) {}

// Constructor for delivery sites
Node::Node(std::string name, NodeType type, double demand, int population)
        : name(name), type(type), maxDeliveryCapacity(0), demand(demand), population(population), currentFlow(0) {}

// Constructor for cities
Node::Node(std::string name, NodeType type, int population)
        : name(name), type(type), maxDeliveryCapacity(0), demand(0), population(population), currentFlow(0) {}

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

int Node::getPopulation() const {
    return population;
}
