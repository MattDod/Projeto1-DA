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
    City
};

class Node {
public:
    Node(std::string name, double id, std::string code, double demand, double population, NodeType type);
    Node(std::string name, std::string municipality, double id, std::string code, double maxDeliveryCapacity); // Constructor for water reservoirs
    Node(double id, std::string code); // Constructor for delivery sites


    // Getter methods
    std::string getName() const;
    std::string getId() const;
    NodeType getType() const;
    double getMaxDeliveryCapacity() const; // For water reservoirs
    double getDemand() const; // For delivery sites
    double getPopulation() const; // For delivery sites and cities

    std::vector<Pipeline *> adj;

private:
    std::string name;
    std::string municipality;
    std::string code;
    double id;
    NodeType type;
    double maxDeliveryCapacity; // For water reservoirs
    double demand; // For delivery sites
    double population; // For delivery sites and cities
    double currentFlow; // For pumping stations
};

#endif //PROJETODA_NODE_H
