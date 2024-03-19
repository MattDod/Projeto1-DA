#include "Node.h"

// Default constructor
Node::Node() : name(""), type(NodeType::WaterReservoir), maxDeliveryCapacity(0), currentFlow(0) {}

// Parameterized constructor
Node::Node(std::string name, NodeType type) : name(name), type(type), maxDeliveryCapacity(0), currentFlow(0) {}

// Constructor for water reservoirs
Node::Node(std::string name, NodeType type, double maxDeliveryCapacity)
        : name(name), type(type), maxDeliveryCapacity(maxDeliveryCapacity), currentFlow(0) {}

// Getter methods
std::string Node::getName() const {
    return name;
}

NodeType Node::getType() const {
    return type;
}

double Node::getCapacity() const {
    return maxDeliveryCapacity;
}
