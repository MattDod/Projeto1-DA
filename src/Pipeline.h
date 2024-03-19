#ifndef PROJETODA_PIPELINE_H
#define PROJETODA_PIPELINE_H

#include "Node.h"

class Pipeline {
public:
    Pipeline(Node* source, Node* target, double capacity);

    // Getter methods
    Node getTarget() const;
    double getCapacity() const;

    // Setter methods (if needed)
    void setCapacity(double capacity);

private:
    Node *targetNode;
    double capacity;
};

#endif //PROJETODA_PIPELINE_H
