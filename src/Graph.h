#ifndef PROJETODA_GRAPH_H
#define PROJETODA_GRAPH_H

#include <vector>
#include <queue>
#include "Node.h"

class Graph {
private:
public:
    // Method to add a node to the graph
    void addNode(Node *node);
    /**
    * @brief Adiciona uma aresta entre dois nós no grafo com capacidade e direção especificadas.
    *
    * Esta função adiciona uma aresta direcionada entre os nós de origem e destino no grafo,
    * com a capacidade e a direção fornecidas. Retorna verdadeiro se a aresta foi adicionada com sucesso,
    * caso contrário, retorna falso se um dos nós não for encontrado no grafo.
    *
    * @param source Código do nó de origem.
    * @param dest Código do nó de destino.
    * @param capacity Capacidade da aresta.
    * @param direction Direção da aresta.
    * @remarks A complexidade temporal desta função é O(V), onde V é o número de vértices no grafo.
    *
    * @return Verdadeiro se a aresta foi adicionada com sucesso, falso caso contrário.
    *
    *
    */
    bool addPipe(std::string &source, std::string &dest, double &capacity, double &direction);
    std::vector<Node *> nodes;
    // Getter method to retrieve all nodes in the graph
    const std::vector<Node *> getNodes() const;
    /**
    * @brief Copia os nós e as arestas de outro grafo para este grafo.
    *
    * Esta função cria cópias de todos os nós e suas arestas do grafo fornecido e adiciona-os a este grafo que será usado com ferramente auxiliar em algoritmos seguintes
    *
    * @param g Grafo a ser copiado.
    *
    * @remarks A complexidade temporal desta função é O(V + E), onde V é o número de vértices e E é o número de arestas no grafo fornecido.
    */
    void copyGraph(const Graph &g);
    /**
    * @brief Encontra um nó no grafo com base no código fornecido.
    *
    * Esta função percorre todos os nós no grafo e retorna o nó com o código correspondente,
    * se encontrado. Se nenhum nó com o código fornecido for encontrado, retorna nullptr.
    *
    * @param code Código do nó a ser encontrado.
    * @remarks A complexidade temporal desta função é O(V), onde V é o número de vértices no grafo.
    *
    * @return Ponteiro para o nó encontrado, ou nullptr se não encontrado.
    *
    *
    */
    Node *findNode(std::string &code) const;
};

#endif // PROJETODA_GRAPH_H
