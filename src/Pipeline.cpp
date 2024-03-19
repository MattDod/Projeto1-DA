#include "Pipeline.h"

// Constructor
Pipeline::Pipeline(Node *source, Node *target, double capacity)
        : targetNode(target), capacity(capacity) {
    // Initialize other members if needed
}

Node * Pipeline::getTarget() const {
    return targetNode;
}

double Pipeline::getCapacity() const {
    return capacity;
}

// Setter methods (if needed)
void Pipeline::setCapacity(double newCapacity) {
    capacity = newCapacity;
}