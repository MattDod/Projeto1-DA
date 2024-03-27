#include "Pipeline.h"

// Constructor
Pipeline::Pipeline(Node *source, Node *target, double capacity, double direction)
        : sourceNode(source), targetNode(target), capacity(capacity), direction(direction) {
    // Initialize other members if needed
}

Node *Pipeline::getSourceNode() const {
    return sourceNode;
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

double Pipeline::getFlow() const {
    return flow;
}

void Pipeline::setFlow(double flow) {
    this->flow = flow;
}

