#include <stdio.h>
#include <stdlib.h>
#include "../../headers/adj_list.h"

// Estrutura para representar um nó em uma lista de adjacências
struct adjListNode
{
    int vertex_id;
    double weight;
    struct adjListNode *next;
};

// Estrutura para representar uma lista de adjacências para um vértice
struct adjList
{
    struct adjListNode *head;
};

// Função para criar um novo nó de lista de adjacências
struct adjListNode *adjListNode_construct(int id, double peso)
{
    struct adjListNode *newNo = (struct adjListNode *)malloc(sizeof(struct adjListNode));
    newNo->vertex_id = id;
    newNo->weight = peso;
    newNo->next = NULL;
    return newNo;
}

adjList *empty_adjList_arr_construct(int n_vertex)
{
    adjList *list = malloc(n_vertex * sizeof(adjList));

    for (int i = 0; i < n_vertex; i++)
    {
        list[i].head = NULL;
    }

    return list;
}

void add_neighbor_to_list(adjList *array_adj, int vertex, int neighbor, double weight)
{
    struct adjListNode *node = adjListNode_construct(neighbor, weight);

    node->next = array_adj[vertex].head;
    array_adj[vertex].head = node;
}

void print_adjList(adjList list)
{
    struct adjListNode *node = list.head;
    while (node != NULL)
    {
        printf("n:%d p:%lf, ", node->vertex_id, node->weight);
        node = node->next;
    }
}
void print_adjList_arr(adjList *list_arr, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {
        printf("%d -> ", i);
        print_adjList(list_arr[i]);
        printf("\n");
    }
}
