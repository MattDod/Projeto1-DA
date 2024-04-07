#ifndef PROJETODA_PIPELINE_H
#define PROJETODA_PIPELINE_H

#include "Node.h"
class Node;
class Pipeline {
public:
    /**
    * @brief Construtor da classe pipeline
    * @param source = no de origem
    * @param target = no de destino
    * @param capacity = capacidade da aresta/pipeline
    * @param direction = indica a direção da pipeline
    */
    Pipeline(Node *source, Node *target, double capacity, double direction);

    // Getter methods
    Node *getSourceNode() const;
    Node *getTarget() const;
    double getCapacity() const;
    double getDirection() const;
    double getFlow() const;

    // Setter methods (if needed)
    void setCapacity(double capacity);
    void setFlow(double flow);

private:
    Node * sourceNode;
    Node * targetNode;
    double capacity;
    double direction;
    double flow;
};

#endif //PROJETODA_PIPELINE_H
