#include "../../headers/heap.h"
#include "../../headers/graph.h"
#include "../../headers/adj_list.h"

#include <float.h>

#define VISITED 1
#define UNVISITED 0
#define INFINITY DBL_MAX
#define NIL -1

typedef struct
{
    // double path_lenght;
    int parent;
    char status;

} vertex_label;

void initialize_heap(Heap *h, int origin)
{
    for (int i = 0; i < get_heap_size(h); i++)
    {
        heap_push(h, i, INFINITY);
    }

    heap_push(h, origin, 0); // set origin vertex
}

void initialize_vtx_label_array(vertex_label *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i].status = UNVISITED;
        array[i].parent = NIL;
    }
}

void update_vertex_label_pathLenght(double *distances_arr, double weight, int v)
{
    if (distances_arr[v] > weight)
    {
        distances_arr[v] = weight;
    }
}
double *dijkstra_algorithm(Graph *graph, int origin)
{

    int n_vertex = graph_get_num_vertex(graph);
    int n_edges = graph_get_num_edges(graph);

    double *distances_arr = malloc(sizeof(double) * n_vertex);
    vertex_label *vertex_labels = malloc(sizeof(vertex_label) * n_vertex);

    Heap *h = heap_construct(n_vertex);

    initialize_heap(h, origin);

    for (int i = 0; i < n_vertex; i++)
    {
        distances_arr[i] = INFINITY;
        vertex_labels[i].parent = NIL;
        vertex_labels[i].status = UNVISITED;
    }

    distances_arr[origin] = 0;

    while (get_heap_size(h) > 0)
    {
        int u = heap_pop(h);

        vertex_labels[u].status = VISITED;

        adjList *adj_list = graph_get_adj_list(graph, u);

        for (int i = 0; i < adj_list_get_size(adj_list); i++)
        {
            int v = adj_list_get_vertex(adj_list, i);
            double weight = adj_list_get_weight(adj_list, i);

            if (vertex_labels[v].status == UNVISITED)
            {
                update_vertex_label_pathLenght(distances_arr, distances_arr[u] + weight, v);
                vertex_labels[v].parent = u;
                heap_push(h, v, distances_arr[v]);
            }
        }
    }

    free(vertex_labels);
    heap_destroy(h);

    return distances_arr;
}
