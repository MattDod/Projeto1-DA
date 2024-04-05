#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include "System.h"

Graph System::getGraph() const {
    return g;
}

System::System(){
    readCities("../data/Cities.csv");
    readStations("../data/Stations.csv");
    readReservoir("../data/Reservoir.csv");
    readPipes("../data/Pipes.csv");
}

void System::readCities(const string &filename) {
    ifstream file(filename);
    string line;
    getline(file, line); // Ignora a primeira linha (cabeçalho)

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return;
    }
    while (getline(file, line)) {
        istringstream s(line);
        string city, code, id, demand, population;
        getline(s, city, ',');
        getline(s, id, ',');
        getline(s, code, ',');
        getline(s, demand, ',');
        getline(s, population, '\r');
        double id2 = stod(id);
        double demand2 = stod(demand);
        double population2 = stod(population);
        Node *nodecity = new Node(city, id2, code, demand2, population2, NodeType::City);
        g.addNode(nodecity);
    }
    file.close();
}

void System::readStations(const string &filename) {
    ifstream file2(filename);
    string line;
    getline(file2, line); // Ignora a primeira linha (cabeçalho)

    if (!file2.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return;
    }
    while (getline(file2, line)) {
        istringstream s(line);
        string code, id;
        getline(s, id, ',');
        getline(s, code, '\r');
        double id2 = stod(id);
        Node *nodecity = new Node(id2, code, NodeType::PumpingStation);
        g.addNode(nodecity);
    }
    file2.close();
}

//Reservoir,Municipality,Id,Code,Maximum Delivery (m3/sec)
void System::readReservoir(const string &filename){
    ifstream file3(filename);
    string line;
    getline(file3, line); // Ignora a primeira linha (cabeçalho)

    if (!file3.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return;
    }
    while (getline(file3, line)) {
        istringstream s(line);
        string reservoir, municipality, id, code, maxDelivery;
        getline(s, reservoir, ',');
        getline(s, municipality, ',');
        getline(s, id, ',');
        getline(s, code, ',');
        getline(s, maxDelivery, '\r');
        double id2 = stod(id);
        double maxDelivery2 = stod(maxDelivery);
        Node *nodecity = new Node(reservoir, municipality, id2, code, maxDelivery2, NodeType::WaterReservoir);
        g.addNode(nodecity);
    }
    file3.close();
}

//Service_Point_A,Service_Point_B,Capacity,Direction
void System::readPipes(const string &filename) {
    ifstream file4(filename);
    string line;
    getline(file4, line); // Ignora a primeira linha (cabeçalho)
    if (!file4.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return;
    }
    while (getline(file4, line)) {
        istringstream s(line);
        string source, target, capacity, direction;
        getline(s, source, ',');
        getline(s, target, ',');
        getline(s, capacity, ',');
        getline(s, direction, '\r');
        double capacity2 = stod(capacity);
        double direction2 = stod(direction);
        auto v1 = g.findNode(source);
        auto v2 = g.findNode(target);
        v1->addPipe(v2, capacity2, direction2);
        //Handling the case where the pipeline is bidirectional
        if(direction2 == 0){
            v2->addPipe(v1, capacity2, direction2);
        }
    }
    file4.close();
}

void System::edmondsKarp(Graph *copy) {
    //Create super source and super sink nodes and add them
    Node* superSource = new Node("SuperSource", NodeType::SuperSource);
    Node* superSink = new Node("SuperSink", NodeType::SuperSink);
    copy->addNode(superSource);
    copy->addNode(superSink);
    for(auto node : copy->getNodes()){
        //Connect super source to water reservoirs ("weight" of the pipeline is the maximum delivery capacity of the reservoir)
        if(node->getType() == NodeType::WaterReservoir){
            superSource->addPipe(node, node->getMaxDeliveryCapacity(), 0);
        }
            //Connect cities (delivery sites) to super sink ("weight" of the pipeline is the demand of the city)
        else if(node->getType() == NodeType::City){
            node->addPipe(superSink, node->getDemand(), 0);
        }
    }

    for (auto n : g.getNodes()){
        for (auto p: n->getAdj()) p->setFlow(0);
    }

    while(findAugmentingPath(copy, superSource, superSink)){
        double bottleneck = findBottleneckCapacity(superSource, superSink);
        updateResidualGraph(superSource, superSink, bottleneck);
    }
}

bool System::findAugmentingPath(Graph *graph, Node *source, Node *sink) {
    for(auto n : graph->getNodes()) n->setVisited(false);

    source->setVisited(true);
    queue<Node *> q;
    q.push(source);

    while(!q.empty() && !sink->isVisited()){
        auto n = q.front();
        q.pop();
        for(auto p: n->getAdj()) {
            if (!p->getTarget()->isVisited() && (p->getCapacity() - p->getFlow()) > 0) {
                p->getTarget()->setVisited(true);
                p->getTarget()->setPath(p);
                q.push(p->getTarget());
            }
        }
        for(auto p: n->getIncoming()) {
            Node* origin = p->getSourceNode();
            if (!origin->isVisited() && p->getFlow() > 0) {
                origin->setVisited(true);
                origin->setPath(p);
                q.push(origin);
            }
        }
    }
    return sink->isVisited();
}

double System::findBottleneckCapacity(Node *source, Node *sink){
    double bottleneck = numeric_limits<double>::max();
    for(auto n = sink; n != source; ){
        auto p = n->getPath();
        if (p->getTarget() == n){
            bottleneck = min(bottleneck, p->getCapacity() - p->getFlow());
            n = p->getSourceNode();
        }
        else{
            bottleneck = min(bottleneck, p->getFlow());
            n = p->getTarget();
        }
    }
    return bottleneck;
}

void System::updateResidualGraph(Node *source, Node *sink, double bottleneck){
    for(auto n = sink; n != source; ){
        auto p = n->getPath();
        if (p->getTarget() == n){
            p->setFlow(p->getFlow() + bottleneck);
            n = p->getSourceNode();
        }
        else{
            p->setFlow(p->getFlow() - bottleneck);
            n = p->getTarget();
        }
    }
}

void System::printFlow(Graph *graph, string choiceCode) {
    cout << "Code" << " " << "Value" << endl;
    if(choiceCode == "all"){
        double maxFlow=0;
        for(auto n : graph->getNodes()){
            if(n->getType() == NodeType::City){
                double flow = 0;
                for(auto p : n->getIncoming()){
                    flow += p->getFlow();
                }
                maxFlow += flow;
                cout << n->getCode() << " " << flow << endl;
            }
        }
        cout<< "Total " << maxFlow << endl;
    }
    else{
        double flow=0;
        Node* n = graph->findNode(choiceCode);
        for(auto p : n->getIncoming()){
            flow+=p->getFlow();
        }
        cout << n->getCode() << " " << flow << endl;
    }
}

void System::cityNeeds(Graph *graph) {
    cout << endl;
    vector<pair<string, double>> met;
    vector<pair<string, double>> notMet;
    for(auto n : graph->getNodes()){
        if(n->getType() == NodeType::City){
            double flow = 0;
            for(auto p : n->getIncoming()){
                flow += p->getFlow();
            }
            double check = n->getDemand() - flow;
            if(check == 0){
                met.push_back(make_pair(n->getCode(), flow));
            }
            else{
                notMet.push_back(make_pair(n->getCode(), check));
            }
        }
    }
    if(!met.empty()){
        cout << "Cities whose demand was met:" << endl << "(Code, Demand)" << endl;
        for(auto p : met){
            cout << p.first << " " << p.second << endl;
        }
    }
    cout << endl;
    if(!notMet.empty()){
        cout << "Cities whose demand was not met:" << endl << "(Code, Deficit)" << endl;
        for(auto p : notMet){
            cout << p.first << " " << p.second << endl;
        }
    }
}

void System::edmondsKarpAvoidNode(Graph *copy, string avoid){
    //Create super source and super sink nodes and add them
    Node* superSource = new Node("SuperSource", NodeType::SuperSource);
    Node* superSink = new Node("SuperSink", NodeType::SuperSink);
    copy->addNode(superSource);
    copy->addNode(superSink);
    for(auto node : copy->getNodes()){
        //Connect super source to water reservoirs ("weight" of the pipeline is the maximum delivery capacity of the reservoir)
        if(node->getType() == NodeType::WaterReservoir){
            superSource->addPipe(node, node->getMaxDeliveryCapacity(), 0);
        }
        //Connect cities (delivery sites) to super sink ("weight" of the pipeline is the demand of the city)
        else if(node->getType() == NodeType::City){
            node->addPipe(superSink, node->getDemand(), 0);
        }
    }

    for (auto n : g.getNodes()){
        n->setVisited(false);
        for (auto p: n->getAdj()) p->setFlow(0);
    }

    while(findAugmentingPathAvoid(copy, superSource, superSink, avoid)){
        double bottleneck = findBottleneckCapacity(superSource, superSink);
        updateResidualGraph(superSource, superSink, bottleneck);
    }
}

bool System::findAugmentingPathAvoid(Graph *graph, Node *source, Node *sink, string avoid){
    //Very similar to findAugmentingPath, but when initializing all nodes' visited status to false
    //Whenever we encounter the node that we want to avoid, we set its visited status to true, so it's never added to the queue
    for(auto n : graph->getNodes()) {
        if(n->getCode() == avoid)
            n->setVisited(true);
        else
            n->setVisited(false);
    }

    source->setVisited(true);
    queue<Node *> q;
    q.push(source);

    while(!q.empty() && !sink->isVisited()){
        auto n = q.front();
        q.pop();
        for(auto p: n->getAdj()) {
            if (!p->getTarget()->isVisited() && (p->getCapacity() - p->getFlow()) > 0) {
                p->getTarget()->setVisited(true);
                p->getTarget()->setPath(p);
                q.push(p->getTarget());
            }
        }
        for(auto p: n->getIncoming()) {
            Node* origin = p->getSourceNode();
            if (!origin->isVisited() && p->getFlow() > 0) {
                origin->setVisited(true);
                origin->setPath(p);
                q.push(origin);
            }
        }
    }
    return sink->isVisited();
}

vector<pair<Node*, double>> System::cityFlowInfo(Graph *graph){
    vector<pair<Node*, double>> cityFlow;
    for(auto node : graph->getNodes()){
        if(node->getType() == NodeType::City){
            double flow = 0;
            for(auto p : node->getIncoming()) flow += p->getFlow();
            cityFlow.push_back(make_pair(node, flow));
        }
    }
    return cityFlow;
}

void System::edmondsKarpAvoidPipeline(Graph *copy, Pipeline *avoid) {
    //Create super source and super sink nodes and add them
    Node* superSource = new Node("SuperSource", NodeType::SuperSource);
    Node* superSink = new Node("SuperSink", NodeType::SuperSink);
    copy->addNode(superSource);
    copy->addNode(superSink);
    for(auto node : copy->getNodes()){
        //Connect super source to water reservoirs ("weight" of the pipeline is the maximum delivery capacity of the reservoir)
        if(node->getType() == NodeType::WaterReservoir){
            superSource->addPipe(node, node->getMaxDeliveryCapacity(), 0);
        }
            //Connect cities (delivery sites) to super sink ("weight" of the pipeline is the demand of the city)
        else if(node->getType() == NodeType::City){
            node->addPipe(superSink, node->getDemand(), 0);
        }
    }
    string avoidSourceCode = avoid->getSourceNode()->getCode();
    string avoidTargetCode = avoid->getTarget()->getCode();

    for (auto n : copy->getNodes()){
        n->setVisited(false);
        for (auto p: n->getAdj()) {
            if((p->getTarget()->getCode() == avoidTargetCode && p->getSourceNode()->getCode() == avoidSourceCode) || (p->getTarget()->getCode() == avoidSourceCode && p->getSourceNode()->getCode() == avoidTargetCode)){
                p->setCapacity(0);
            }
            p->setFlow(0);
        }
    }

    while(findAugmentingPath(copy, superSource, superSink )){
        double bottleneck = findBottleneckCapacity(superSource, superSink);
        updateResidualGraph(superSource, superSink, bottleneck);
    }
}
