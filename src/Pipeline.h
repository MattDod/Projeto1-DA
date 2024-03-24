#ifndef PROJETODA_PIPELINE_H
#define PROJETODA_PIPELINE_H

#include "Node.h"
class Node;
class Pipeline {
public:
    Pipeline(Node *source, Node *target, double capacity, double direction);

    // Getter methods
    Node  * getTarget() const;
    double getCapacity() const;
    double getDirection() const;

    // Setter methods (if needed)
    void setCapacity(double capacity);

private:
    Node * targetNode;
    double capacity;
    double direction;
    ;
};

#endif //PROJETODA_PIPELINE_H
