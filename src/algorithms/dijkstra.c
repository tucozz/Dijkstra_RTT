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
    int n_univisited = n_vertex;

    // constroying heap
    Heap *heap = heap_construct(n_vertex);
    // constroying dijsktra table
    vertex_label *vertex_label_arr = malloc(sizeof(vertex_label) * n_vertex);
    initialize_vtx_label_array(vertex_label_arr, n_vertex);

    double *distances_arr = malloc(sizeof(double) * n_vertex);
    for (int i = 0; i < n_vertex; i++)
    {
        distances_arr[i] = INFINITY;
    }
    distances_arr[origin] = 0;

    adjList **arr_adjList = graph_get_arr_adjList(graph);

    initialize_heap(heap, origin);

    while (!heap_empty(heap))
    {
        int current_v = heap_pop(heap);

        adjList *current_adjList = get_adjList(arr_adjList, current_v);

        Iterator *it = createIterator(current_adjList);

        while (hasCurrent(it))
        {

            vtx_weight_pair edge = getCurrent(it);

            int vtx_id = edge.vertex_id;
            double weight = edge.weight;

            //evita overflow
            double distance = INFINITY;
            if(distances_arr[current_v] != INFINITY){
                distance = distances_arr[current_v] + weight;
            }

            if (vertex_label_arr[vtx_id].status == UNVISITED)
            {
                heap_push(heap, vtx_id, distance); // atualiza no heap
                vertex_label_arr[vtx_id].parent = current_v;
                update_vertex_label_pathLenght(distances_arr, distance, vtx_id);
            }

            next(it);
        }

        vertex_label_arr[current_v].status = VISITED;
        n_univisited--; // number of unvisited vertex

        destroyIterator(it);
    }

    heap_destroy(heap);
    free(vertex_label_arr);

    // DEBUG PRINT
    // printf("Distances %d:\n", origin);
    // for (int i = 0; i < n_vertex; i++)
    // {
    //     if (distances_arr[i] != INFINITY)
    //         printf("%d: %lf, \n", i, distances_arr[i]);
    //     else
    //         printf("%d: DEU ERRADO, CAMINHO NAO ENCONTRADO, \n", i);
    // }
    // printf("\n");
    

    return distances_arr;
}
