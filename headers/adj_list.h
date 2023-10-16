#include <stdio.h>
#include <stdlib.h>

// Função para criar um grafo com um número especificado de vértices
struct Grafo* criarGrafo(int numVertices);

// Função para adicionar uma aresta direcionada de u para v no grafo
void adicionarAresta(struct Grafo* grafo, int u, int v);