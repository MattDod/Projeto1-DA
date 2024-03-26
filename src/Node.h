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
    City,
    SuperSource,
    SuperSink
};

class Node {
public:
    Node(std::string name, double id, std::string code, double demand, double population, NodeType type);
    Node(std::string name, std::string municipality, double id, std::string code, double maxDeliveryCapacity, NodeType type); // Constructor for water reservoirs
    Node(double id, std::string code, NodeType type); // Constructor for delivery sites
    Node(std::string code, NodeType type); // Constructor for super source/sink


    // Getter methods
    std::string getName() const;
    std::string getMunicipality() const;
    std::string getCode() const;
    double getId() const;
    NodeType getType() const;
    double getMaxDeliveryCapacity() const; // For water reservoirs
    double getDemand() const; // For delivery sites
    double getPopulation() const; // For delivery sites and cities
    Pipeline *getPath() const;


    Pipeline * addPipe(Node *dest, double capacity, double direction);
    bool isVisited() const;
    void setVisited(bool value);
    void setPath(Pipeline *path);
    std::vector<Pipeline *> getAdj() const;


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
    bool visited = false;
    Pipeline *path = nullptr;
};

#endif //PROJETODA_NODE_H
