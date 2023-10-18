#ifndef _GRAPH_H_
#define _GRAPH_H_

#define SERVER 's'
#define CLIENT 'c'
#define MONITOR 'm'

typedef struct Graph Graph;

Graph *graph_construct(int num_vertex);

void add_edge_u_to_v(struct Graph *graph, int u, int v, double weight);
void print_graph(Graph *g);
void define_vertex_type(Graph *graph, int vertex, char type);

#endif