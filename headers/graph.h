#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "adj_list.h"

#define SERVER 's'
#define CLIENT 'c'
#define MONITOR 'm'

typedef struct Graph Graph;

Graph *graph_construct(size_t num_vertex, size_t n_server, size_t n_client, size_t n_monitor);
void add_edge_u_to_v(struct Graph *graph, int u, int v, double weight);
void print_graph(Graph *g);
void define_vertex_type(Graph *graph, int vertex, char type);
int graph_get_num_vertex(Graph *graph);
adjList *graph_get_arr_adjList(Graph *g);

#endif