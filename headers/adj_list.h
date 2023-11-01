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
typedef struct Iterator Iterator;
typedef struct vtx_weight_pair vtx_weight_pair;

// adjList functions
adjList **empty_adjList_arr_construct(int n_vertex);
void print_adjList_arr(adjList **list_arr, int arr_size);
void adjList_arr_destroy(adjList **list_arr, int arr_size);
void add_neighbor_to_list(adjList **array_adj, int vertex, int neighbor, double weight);

// get functions
int get_id_vtx_weight_pair(vtx_weight_pair a);
double get_weight_vtx_weight_pair(vtx_weight_pair a);
adjList *get_adjList(adjList **array, int current_v);

// iterator funcitons
void next(Iterator *iterator);
int has_next(Iterator *iterator);
int hasCurrent(Iterator *iterator);
Iterator *createIterator(adjList *lista);
void destroyIterator(Iterator *iterator);
vtx_weight_pair getCurrent(Iterator *iterator);

#endif