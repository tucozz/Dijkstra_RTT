#include <stdio.h>
#include <stdlib.h>
#include "../../headers/adj_list.h"

int get_id_vtx_weight_pair(vtx_weight_pair a)
{
    return a.vertex_id;
}

double get_weight_vtx_weight_pair(vtx_weight_pair a)
{
    return a.weight;
}

// Estrutura para representar um nó em uma lista de adjacências
struct adjListNode
{
    int vertex_id;
    double weight;
    struct adjListNode *next;
};

struct adjList
{
    struct adjListNode *head;
};

// Estrutura para representar uma lista de adjacências para um vértice

// Função para criar um novo nó de lista de adjacências
struct adjListNode *adjListNode_construct(int id, double peso)
{
    struct adjListNode *newNo = (struct adjListNode *)malloc(sizeof(struct adjListNode));
    newNo->vertex_id = id;
    newNo->weight = peso;
    newNo->next = NULL;
    return newNo;
}

adjList **empty_adjList_arr_construct(int n_vertex)
{
    adjList **list = malloc(n_vertex * sizeof(adjList));

    for (int i = 0; i < n_vertex; i++)
    {
        list[i] = (adjList *)malloc(sizeof(adjList));
        list[i]->head = NULL;
    }

    return list;
}

void adjlist_destroy(adjList *list)
{
    struct adjListNode *node = list->head;
    struct adjListNode *next_node = NULL;
    while (node != NULL)
    {
        next_node = node->next;
        free(node);
        node = next_node;
    }
    free(list);
}

void adjList_arr_destroy(adjList **list_arr, int arr_size){
    for(int i = 0; i < arr_size; i++){
        adjlist_destroy(list_arr[i]);
    }
    free(list_arr);
}

void add_neighbor_to_list(adjList **array_adj, int vertex, int neighbor, double weight)
{
    struct adjListNode *node = adjListNode_construct(neighbor, weight);

    if(array_adj[vertex] == NULL){
        array_adj[vertex] = (adjList *)malloc(sizeof(adjList));
    }

    node->next = array_adj[vertex]->head;
    array_adj[vertex]->head = node;
}

void print_adjList(adjList *list)
{
    struct adjListNode *node = list->head;
    while (node != NULL)
    {
        printf("n:%d p:%lf, ", node->vertex_id, node->weight);
        node = node->next;
    }
}
void print_adjList_arr(adjList **list_arr, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {
        printf("%d -> ", i);
        print_adjList(list_arr[i]);
        printf("\n");
    }
}

adjList *get_adjList(adjList **array, int current_v)
{
    return array[current_v];
}

// implementação de um iterador para lista encadeada de adj **********************

struct Iterator
{
    struct adjListNode *current; // Nó atual do iterador
};

Iterator *createIterator(adjList *lista)
{
    Iterator *iterator = (Iterator *)malloc(sizeof(Iterator));
    if (iterator == NULL)
    {
        perror("Erro ao alocar memória para o iterador");
        exit(1);
    }
    iterator->current = lista->head;
    return iterator;
}

void destroyIterator(Iterator *iterator)
{
    free(iterator);
}

void next(Iterator *iterator)
{
    if (iterator != NULL && iterator->current != NULL)
    {
        iterator->current = iterator->current->next;
    }
}

int has_next(Iterator *iterator)
{
    return (iterator->current->next != NULL);
}

vtx_weight_pair getCurrent(Iterator *iterator)
{
    vtx_weight_pair edge;
    edge.vertex_id = iterator->current->vertex_id;
    edge.weight = iterator->current->weight;

    return edge;
}

int hasCurrent(Iterator *iterator)
{
    if (iterator->current)
    {
        return 1;
    }
    else
        return 0;
}