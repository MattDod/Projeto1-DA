#ifndef PROJETODA_NODE_H
#define PROJETODA_NODE_H

#include <string>
#include <vector>
class Pipeline;
#include "Pipeline.h"


// Enum to represent the type of node
enum class NodeType {
    WaterReservoir,
    PumpingStation,
    DeliverySite,
    City
};

class Node {
public:
    Node();
    Node(std::string name, NodeType type);
    Node(std::string name, NodeType type, double maxDeliveryCapacity); // Constructor for water reservoirs
    Node(std::string name, NodeType type, double demand, int population); // Constructor for delivery sites
    Node(std::string name, NodeType type, int population); // Constructor for cities

    // Getter methods
    std::string getName() const;
    NodeType getType() const;
    double getMaxDeliveryCapacity() const; // For water reservoirs
    double getDemand() const; // For delivery sites
    int getPopulation() const; // For delivery sites and cities

    std::vector<Pipeline *> adj;

private:
    std::string name;
    NodeType type;
    double maxDeliveryCapacity; // For water reservoirs
    double demand; // For delivery sites
    int population; // For delivery sites and cities
    double currentFlow; // For pumping stations
};

#endif //PROJETODA_NODE_H
