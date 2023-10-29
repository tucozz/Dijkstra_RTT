#ifndef _ADJ_LIST_H_
#define _ADJ_LIST_H_
#include <stdio.h>
#include <stdlib.h>

struct vtx_weight_pair
{
    int vertex_id;
    double weight;
};

typedef struct adjList adjList;
typedef struct vtx_weight_pair vtx_weight_pair;
typedef struct Iterator Iterator;

double get_weight_vtx_weight_pair(vtx_weight_pair a);
int get_id_vtx_weight_pair(vtx_weight_pair a);

adjList *get_adjList(adjList **array, int current_v);

adjList **empty_adjList_arr_construct(int n_vertex);
void add_neighbor_to_list(adjList **array_adj, int vertex, int neighbor, double weight);

struct AdjListNode *AdjListNode_construct(int destino, double peso);
void adjList_arr_destroy(adjList **list_arr, int arr_size);
void print_adjList_arr(adjList **list_arr, int arr_size);

int adj_list_get_size(adjList *list);
int adj_list_get_vertex(adjList *list, int index);
double adj_list_get_weight(adjList *list, int index);

// iterator funcitons
Iterator *createIterator(adjList *lista);
void destroyIterator(Iterator *iterator);
void next(Iterator *iterator);
int has_next(Iterator *iterator);
vtx_weight_pair getCurrent(Iterator *iterator);
int hasCurrent(Iterator *iterator);

#endif