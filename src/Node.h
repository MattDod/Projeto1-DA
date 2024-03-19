#ifndef PROJETODA_NODE_H
#define PROJETODA_NODE_H

#include <string>
#include <vector>
#include "Pipeline.h"

// Enum to represent the type of node
enum class NodeType {
    WaterReservoir,
    PumpingStation,
    DeliverySite
};

class Node {
public:
    Node();
    Node(std::string name, NodeType type);
    Node(std::string name, NodeType type, double maxDeliveryCapacity); // Constructor for water reservoirs
    // Getter methods
    std::string getName() const;
    NodeType getType() const;
    double getCapacity() const; // For reservoirs and pumping stations

    std::vector<Pipeline> adj;

private:
    std::string name;
    NodeType type;
    double maxDeliveryCapacity; // For water reservoirs
    double currentFlow; // For pumping stations
};


#endif //PROJETODA_NODE_H
