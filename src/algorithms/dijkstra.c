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

    // get number of vertex
    int n_vertex = graph_get_num_vertex(graph);
    int n_univisited = n_vertex;

    // construct heap
    Heap *heap = heap_construct(n_vertex);
    // construct dijsktra table
    vertex_label *vertex_label_arr = malloc(sizeof(vertex_label) * n_vertex);
    initialize_vtx_label_array(vertex_label_arr, n_vertex);

    // construct distances array and set origin distance to 0
    double *distances_arr = malloc(sizeof(double) * n_vertex);
    for (int i = 0; i < n_vertex; i++)
    {
        distances_arr[i] = INFINITY;
    }
    distances_arr[origin] = 0;

    // get all adjList from the graph
    adjList **arr_adjList = graph_get_arr_adjList(graph);

    // initialize heap
    initialize_heap(heap, origin);

    // while there is unvisited vertex
    while (!heap_empty(heap))
    {
        // get the vertex with the smallest distance
        int current_v = heap_pop(heap);

        // get the adjList from the current vertex
        adjList *current_adjList = get_adjList(arr_adjList, current_v);

        // iterate over the adjList
        Iterator *it = createIterator(current_adjList);
        while (hasCurrent(it))
        {
            // get the current vertex and weight
            vtx_weight_pair edge = getCurrent(it);

            int vtx_id = edge.vertex_id;
            double weight = edge.weight;

            //avoid overflow
            double distance = INFINITY;
            if(distances_arr[current_v] != INFINITY){
                distance = distances_arr[current_v] + weight;
            }

            // if the vertex is unvisited
            if (vertex_label_arr[vtx_id].status == UNVISITED)
            {
                // update the distance
                heap_push(heap, vtx_id, distance); // atualiza no heap
                vertex_label_arr[vtx_id].parent = current_v;
                update_vertex_label_pathLenght(distances_arr, distance, vtx_id);
            }

            next(it);
        }

        // set the current vertex as visited
        vertex_label_arr[current_v].status = VISITED;
        n_univisited--; // number of unvisited vertex

        destroyIterator(it);
    }

    // free memory
    heap_destroy(heap);
    free(vertex_label_arr);
    
    return distances_arr;
}
