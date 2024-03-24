#include "Pipeline.h"

// Constructor
Pipeline::Pipeline(Node *source, Node *target, double capacity, double direction)
        : targetNode(target), capacity(capacity), direction(direction) {
    // Initialize other members if needed
}

Node * Pipeline::getTarget() const {
    return targetNode;
}

double Pipeline::getCapacity() const {
    return capacity;
}
double Pipeline::getDirection() const{
    return direction;
}

// Setter methods (if needed)
void Pipeline::setCapacity(double newCapacity) {
    capacity = newCapacity;
}