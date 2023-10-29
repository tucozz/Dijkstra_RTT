#include <stdlib.h>
#include <stdio.h>
#include "../../headers/input_reader.h"
// #include "../../headers/graph.h"

Graph *graph_read(char *filepath)
{

    int n_vertex = 0, n_edges = 0;
    int n_server = 0, n_client = 0, n_monitor = 0;
    int aux = 0;
    int adj = 0;
    double distance = 0;

    FILE *file = fopen(filepath, "r");

    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo %s!\n", filepath);
        exit(1);
    }

    fscanf(file, "%d %d\n", &n_vertex, &n_edges);
    fscanf(file, "%d %d %d\n", &n_server, &n_client, &n_monitor);

    Graph *graph = graph_construct(n_vertex, n_edges, n_server, n_client, n_monitor); // constroi grafo

    for (int s = 0; s < n_server; s++)
    {
        fscanf(file, "%d\n", &aux); // define como servidor
        define_vertex_type(graph, aux, SERVER);
        graph_set_server_idx(graph, s, aux);
    }

    for (int c = 0; c < n_client; c++)
    {
        fscanf(file, "%d\n", &aux); // define como cliente
        define_vertex_type(graph, aux, CLIENT);
        graph_set_client_idx(graph, c, aux);
    }

    for (int m = 0; m < n_monitor; m++)
    {
        fscanf(file, "%d\n", &aux); // define como monitor
        define_vertex_type(graph, aux, MONITOR);
        graph_set_monitor_idx(graph, m, aux);
    }

    for (int e = 0; e < n_edges; e++)
    {
        fscanf(file, "%d %d %lf\n", &aux, &adj, &distance); // montar lista de adjacencia
        add_edge_u_to_v(graph, aux, adj, distance);
    }

    //FOR DEBUGGING
    //print_graph(graph);

    fclose(file);
    return graph;
}
