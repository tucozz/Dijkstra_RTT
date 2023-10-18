#ifndef _ADJ_LIST_H_
#define _ADJ_LIST_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct adjList adjList;

adjList *empty_adjList_arr_construct(int n_vertex);
void add_neighbor_to_list(adjList *array_adj, int vertex, int neighbor, double weight);

struct AdjListNode *AdjListNode_construct(int destino, double peso);
void print_adjList_arr(adjList *list_arr, int arr_size);

#endif