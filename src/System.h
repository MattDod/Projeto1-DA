//
// Created by kamert on 19-03-2024.
//

#ifndef PROJETODA_SYSTEM_H
#define PROJETODA_SYSTEM_H

#include "Graph.h"

using namespace std;
class System{
private:
    Graph g;
public:
    Graph getGraph() const;
    /**
    * @brief O construtor faz 3 chamadas, cada uma faz o parsing da informação dos ficheiros fornecidos
     *@param n recebe parametros
    */
    System();
    /**
    * @brief Faz o parsing das Cidades
    * @param filename = nome do ficheiro
    */
    void readCities(const string &filename);
    /**
    * @brief Faz o parsing das Pipes
    * @param filename = nome do ficheiro
    */
    void readPipes(const string &filename);
    /**
    * @brief Faz o parsing dos Reservatórios
    * @param filename = nome do ficheiro
    */
    void readReservoir(const string &filename);
    /**
    * @brief Faz o parsing das Stations
    * @param filename = nome do ficheiro
    */
    void readStations(const string &filename);

    //Normal Edmonds-Karp algorithm functions


    /**
    * @brief Implementa o algoritmo de Edmonds-Karp para encontrar o fluxo máximo em uma rede de fluxo.
    *
    * Esta função cria um super nó de origem e um super nó de destino, conectando os reservatórios de água ao super nó de origem
    * e as cidades ao super nó de destino. Em seguida, itera sobre o grafo residual, encontrando "Augmenting Paths" e
    * atualizando o grafo residual até que não seja possível encontrar mais caminhos.
    *
    * @param Ponteiro para o grafo de fluxo residual onde o algoritmo será executado.
    *
    * @remarks A complexidade temporal deste algoritmo é O(V * E^2), onde V é o número de vértices no grafo e E é o número de arestas.
    */
    void edmondsKarp(Graph *copy);
    /**
    * @brief Encontra um "augmenting path" no grafo residual.
    *
    * Esta função realiza uma busca em largura (BFS) para encontrar um caminho no grafo residual.
    *
    * @param graph Ponteiro para o grafo residual.
    * @param source Ponteiro para o nó de origem.
    * @param sink Ponteiro para o nó de destino.
     *
    * @remarks A complexidade temporal desta função é O(V + E), onde V é o número de vértices e E é o número de arestas no grafo residual.
    * @return Verdadeiro se um caminho de aumento for encontrado, falso caso contrário.
    */
    bool findAugmentingPath(Graph *graph, Node *source, Node *sink);
    /**
    * @brief Encontra a capacidade do gargalo ao longo do caminho de aumento.
    *
    * Esta função calcula a capacidade do gargalo ao longo do caminho de aumento, que é o menor valor de capacidade residual
    * ao longo do mesmo.
    *
    * @param source Ponteiro para o nó de origem do caminho de aumento.
    * @param sink Ponteiro para o nó de destino do caminho de aumento.
    * @return A capacidade do gargalo ao longo do caminho de aumento.
    *
    * @remarks A complexidade temporal desta função é O(V), onde V é o número de nós no caminho de aumento.
    */
    double findBottleneckCapacity(Node *source, Node *sink);
    /**
    * @brief Atualiza o grafo residual após encontrar um caminho de aumento.
    *
    * Esta função atualiza o grafo residual após encontrar um caminho de aumento, ajustando os fluxos nas arestas
    * de acordo com a capacidade do gargalo ao longo do caminho de aumento.
    *
    * @param source Ponteiro para o nó de origem do caminho de aumento.
    * @param sink Ponteiro para o nó de destino do caminho de aumento.
    * @param bottleneck Capacidade do gargalo ao longo do caminho de aumento.
    *
    * @remarks A complexidade temporal desta função é O(V), onde V é o número de nós no caminho de aumento.
    */
    void updateResidualGraph(Node *source, Node *sink, double bottleneck);
    /**
    * @brief Imprime o fluxo de cada cidade ou o fluxo total, dependendo da escolha.
    *
    * Esta função imprime o fluxo de cada cidade ou o fluxo total, dependendo da escolha do usuário.
    *
    * @param graph Ponteiro para o grafo.
    * @param choiceCode Código da cidade ou "all" para imprimir o fluxo de todas as cidades.
    *
    * @remarks A complexidade temporal desta função é O(V), onde V é o número de nós no grafo.
    */
    void printFlow(Graph *graph, string choiceCode);
    /**
    * @brief Verifica as necessidades de cada cidade e imprime aquelas cuja demanda foi atendida e aquelas cuja demanda não foi atendida.
    *
    * Esta função calcula o fluxo total de entrada em cada cidade e verifica se a demanda foi atendida. Em seguida, imprime as cidades
    * cuja demanda foi atendida e as que não foram atendidas.
    *
    * @param graph Ponteiro para o grafo.
    *
    * @remarks A complexidade temporal desta função é O(V), onde V é o número de nós no grafo.
    */
    void cityNeeds(Graph *graph);

    //Special Edmonds-Karp algorithm functions

    /**
    * @brief Implementa o algoritmo de Edmonds-Karp para encontrar o fluxo máximo em uma rede de fluxo, evitando um determinado nó.
    *
    * Esta função cria um super nó de origem e um super nó de destino, conectando os reservatórios de água ao super nó de origem
    * e as cidades ao super nó de destino. Em seguida, itera sobre o grafo residual, encontrando caminhos aumentantes e
    * atualizando o grafo residual até que não seja possível encontrar mais caminhos aumentantes, evitando um nó específico.
    *
    * @param copy Ponteiro para o grafo de fluxo residual onde o algoritmo será executado.
    * @param avoid Código do nó a ser evitado durante a execução do algoritmo.
    *
    * @remarks A complexidade temporal deste algoritmo é O(V * E^2), onde V é o número de vértices no grafo e E é o número de arestas.
    */
    void edmondsKarpAvoidNode(Graph *copy, string avoid);
    /**
    * @brief Implementa o algoritmo de Edmonds-Karp para encontrar o fluxo máximo em uma rede de fluxo, evitando um determinado pipeline.
    *
    * Esta função cria um super nó de origem e um super nó de destino, conectando os reservatórios de água ao super nó de origem
    * e as cidades ao super nó de destino. Em seguida, itera sobre o grafo residual, encontrando caminhos aumentantes e
    * atualizando o grafo residual até que não seja possível encontrar mais caminhos aumentantes, evitando uma pipeline específico.
    *
    * @param copy Ponteiro para o grafo de fluxo residual onde o algoritmo será executado.
    * @param avoid Ponteiro para o pipeline a ser evitado durante a execução do algoritmo.
    *
    * @remarks A complexidade temporal deste algoritmo é O(V * E^2), onde V é o número de vértices no grafo e E é o número de arestas.
    */
    void edmondsKarpAvoidPipeline(Graph *copy, Pipeline *avoid);
    /**
    * @brief Encontra um caminho de aumento no grafo residual, evitando um determinado nó.
    *
    * Esta função realiza uma busca em largura (BFS) para encontrar um caminho de aumento no grafo residual,
    * evitando um nó específico durante a busca.
    *
    * @param graph Ponteiro para o grafo residual.
    * @param source Ponteiro para o nó de origem.
    * @param sink Ponteiro para o nó de destino.
    * @param avoid Código do nó a ser evitado durante a busca.
    * @remarks A complexidade temporal desta função é O(V + E), onde V é o número de vértices no grafo e E é o número de arestas.
    * @return Verdadeiro se um caminho de aumento for encontrado, falso caso contrário.
    *
    *
    */
    bool findAugmentingPathAvoid(Graph *graph, Node *source, Node *sink, string avoid);
    /**
    * @brief Retorna informações sobre o fluxo de cada cidade no grafo.
    *
    * Esta função calcula o fluxo total de entrada em cada cidade no grafo e retorna um vetor que contém
    * pares de ponteiros para os nós das cidades e seus fluxos correspondentes.
    *
    * @param graph Ponteiro para o grafo.
    * @remarks A complexidade temporal desta função é O(V + E), onde V é o número de vértices no grafo e E é o número de arestas.
    * @return Um vetor de pares, onde cada par consiste em um ponteiro para um nó de cidade e o fluxo correspondente.
    *
    *
    */
    vector<pair<Node*, double>> cityFlowInfo(Graph *graph);

};
#endif //PROJETODA_SYSTEM_H
