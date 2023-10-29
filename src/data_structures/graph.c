#include "../../headers/graph.h"
//#include "../../headers/adj_list.h"

struct Graph
{
    char *vertex_type; // client out servidor or monitor
    adjList *adj_list;
    int *servers_idx;
    int *clients_idx;
    int *monitors_idx;
    int n_vertex;
    int n_servers;
    int n_clients;
    int n_monitors;
};

Graph *graph_construct(size_t num_vertex, size_t n_server, size_t n_client, size_t n_monitor)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->n_vertex = num_vertex;

    graph->adj_list = (adjList *)empty_adjList_arr_construct(num_vertex);

    graph->vertex_type = (char *)calloc(num_vertex, sizeof(char)); // ver se o calloc zera todos os bits

    graph->servers_idx = (int *)calloc(n_server, sizeof(int)); // aloca vetor de servidores
    graph->clients_idx = (int *)calloc(n_client, sizeof(int)); // aloca vetor de clientes
    graph->monitors_idx = (int *)calloc(n_monitor, sizeof(int)); // aloca vetor de monitores

    graph->n_servers = n_server;
    graph->n_clients = n_client;
    graph->n_monitors = n_monitor;
    
    return graph;
}

void graph_destroy(Graph *graph)
{
    free(graph->vertex_type);
    free(graph->servers_idx);
    free(graph->clients_idx);
    free(graph->monitors_idx);
    free(graph);
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

int graph_get_num_servers(Graph *graph)
{
    return graph->n_servers;
}

int graph_get_num_clients(Graph *graph)
{
    return graph->n_clients;
}

int graph_get_num_monitors(Graph *graph)
{
    return graph->n_monitors;
}

int *graph_get_servers(Graph *graph)
{
    return graph->servers_idx;
}

int *graph_get_clients(Graph *graph)
{
    return graph->clients_idx;
}

int *graph_get_monitors(Graph *graph)
{
    return graph->monitors_idx;
}

char *graph_get_vertex_type(Graph *graph)
{
    return graph->vertex_type;
}

adjList *graph_get_arr_adjList(Graph *g)
{
    return g->adj_list;
}

int graph_get_server_index(Graph *graph, int server)
{
    return graph->servers_idx[server];
}

int graph_get_client_index(Graph *graph, int client)
{
    return graph->clients_idx[client];
}

int graph_get_monitor_index(Graph *graph, int monitor)
{
    return graph->monitors_idx[monitor];
}

void graph_set_server_idx(Graph *graph, int server, int idx)
{
    graph->servers_idx[server] = idx;
}

void graph_set_client_idx(Graph *graph, int client, int idx)
{
    graph->clients_idx[client] = idx;
}

void graph_set_monitor_idx(Graph *graph, int monitor, int idx)
{
    graph->monitors_idx[monitor] = idx;
}