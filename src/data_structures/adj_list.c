#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó em uma lista de adjacências
struct AdjListNode {
    int destino;
    double peso;
    struct AdjListNode* proximo;
};

// Estrutura para representar uma lista de adjacências para um vértice
struct AdjList {
    struct AdjListNode* cabeca;
};

// Estrutura para representar um grafo com um número fixo de vértices
struct Grafo {
    int numVertices;
    struct AdjList* listaAdjacencias;
};

// Função para criar um novo nó de lista de adjacências
struct AdjListNode* criarAdjListNode(int destino, float peso) {
    struct AdjListNode* novoNo = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    novoNo->destino = destino;
    novoNo->proximo = NULL;
    return novoNo;
}

// Função para criar um grafo com um número especificado de vértices
struct Grafo* criarGrafo(int numVertices) {
    struct Grafo* grafo = (struct Grafo*)malloc(sizeof(struct Grafo));
    grafo->numVertices = numVertices;

    // Aloca memória para a matriz de listas de adjacências
    grafo->listaAdjacencias = (struct AdjList*)malloc(numVertices * sizeof(struct AdjList));

    // Inicializa todas as listas de adjacências como vazias
    for (int i = 0; i < numVertices; ++i) {
        grafo->listaAdjacencias[i].cabeca = NULL;
    }

    return grafo;
}

// Função para adicionar uma aresta direcionada de u para v no grafo
void adicionarAresta(struct Grafo* grafo, int u, int v, float peso) {
    struct AdjListNode* novoNo = criarAdjListNode(v, peso);
    novoNo->proximo = grafo->listaAdjacencias[u].cabeca;
    grafo->listaAdjacencias[u].cabeca = novoNo;
}