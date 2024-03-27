#ifndef PROJETODA_PIPELINE_H
#define PROJETODA_PIPELINE_H

#include "Node.h"
class Node;
class Pipeline {
public:
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
