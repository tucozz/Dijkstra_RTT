#include "../../headers/graph.h"
//#include "../../headers/adj_list.h"

struct Graph
{
    int n_vertex;
    char *vertex_type; // client out servidor or monitor
    adjList *adj_list;
    int *servers_idx;
    int *clients_idx;
    int *monitors_idx;
};

Graph *graph_construct(size_t num_vertex, size_t n_server, size_t n_client, size_t n_monitor)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->n_vertex = num_vertex;

    graph->adj_list = (adjList *)empty_adjList_arr_construct(num_vertex);

    graph->vertex_type = (char *)calloc(num_vertex, sizeof(char)); // ver se o calloc zera todos os bits

    graph->servers_idx = (int *)malloc(n_server * sizeof(int)); // aloca vetor de servidores
    graph->clients_idx = (int *)malloc(n_client * sizeof(int)); // aloca vetor de clientes
    graph->monitors_idx = (int *)malloc(n_monitor * sizeof(int)); // aloca vetor de monitores
    
    return graph;
}

void add_edge_u_to_v(struct Graph *graph, int u, int v, double weight)
{
    add_neighbor_to_list(graph->adj_list, u, v, weight);
}

void print_graph(Graph *g)
{
    print_adjList_arr(g->adj_list, g->n_vertex);
    printf("\n");
    for (int i = 0; i < g->n_vertex; i++)
    {
        printf("%d = %c\n", i, g->vertex_type[i]);
    }
}

void define_vertex_type(Graph *graph, int vertex, char type)
{
    graph->vertex_type[vertex] = type;
}

int graph_get_num_vertex(Graph *graph)
{
    return graph->n_vertex;
}

adjList *graph_get_arr_adjList(Graph *g)
{
    return g->adj_list;
}