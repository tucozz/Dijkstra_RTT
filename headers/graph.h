#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "adj_list.h"

#define SERVER 's'
#define CLIENT 'c'
#define MONITOR 'm'

typedef struct Graph Graph;

void print_graph(Graph *g);
void graph_destroy(Graph *graph);
void add_edge_u_to_v(struct Graph *graph, int u, int v, double weight);
Graph *graph_construct(size_t num_vertex, size_t n_server, size_t n_client, size_t n_monitor);

// Getters and setters
int *graph_get_clients(Graph *graph);
int *graph_get_servers(Graph *graph);
int *graph_get_monitors(Graph *graph);
int graph_get_num_vertex(Graph *graph);
int graph_get_num_clients(Graph *graph);
int graph_get_num_servers(Graph *graph);
int graph_get_num_monitors(Graph *graph);
adjList **graph_get_arr_adjList(Graph *g);
char *graph_get_vertex_type(Graph *graph);
char graph_get_vertex_type_index(Graph *graph, int idx);
int graph_get_server_index(Graph *graph, int server_id);
int graph_get_client_index(Graph *graph, int client_id);
int graph_get_monitor_index(Graph *graph, int monitor_id);
void define_vertex_type(Graph *graph, int vertex, char type);
void graph_set_server_idx(Graph *graph, int index, int server_id);
void graph_set_client_idx(Graph *graph, int index, int client_id);
void graph_set_monitor_idx(Graph *graph, int index, int monitor_id);

#endif