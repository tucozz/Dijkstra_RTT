#include "heap.h"
#include <stdlib.h>

typedef struct
{
    int data;
    double priority;
}HeapNode;

struct Heap
{
    int *positions;
    HeapNode *nodes;
    int size;
    int capacity;
};

static int node_idx_parent(int idx){return (int)(idx - 1)/2;}

static int node_idx_left_child(int idx){return 2*idx + 1;}

static int node_idx_right_child(int idx){return 2*idx + 2;}

static void _heapify_idx_swap(Heap *heap, int idx1, int idx2){
    //muda na tabela primeiro
    int auxpos = heap->positions[idx1];
    heap->positions[idx1] = heap->positions[idx2];
    heap->positions[idx2] = auxpos;

    //depois muda no heap mesmo
    HeapNode auxnode = heap->nodes[idx1];
    heap->nodes[idx1] = heap->nodes[idx2];
    heap->nodes[idx2] = auxnode;
}

static int _heapify(Heap *h, int idx_init){
    if(h->size == 0)
        return idx_init;
    
    int current = idx_init;
    while(current != 0 && h->nodes[node_idx_parent(current)].priority > h->nodes[current].priority){
        _heapify_idx_swap(h, current, node_idx_parent(current));
        current = node_idx_parent(current);
    }

    return current;
}

static int _heapify_down(Heap *h, int idx_init){
    int current = idx_init;

    while(node_idx_right_child(current) < h->size && (h->nodes[node_idx_left_child(current)].priority < h->nodes[current].priority
                            || h->nodes[node_idx_right_child(current)].priority < h->nodes[current].priority)){

        if(h->nodes[node_idx_left_child(current)].priority < h->nodes[node_idx_right_child(current)].priority){
            _heapify_idx_swap(h, node_idx_left_child(current), current);
            current = node_idx_left_child(current);
        }
        else if (h->nodes[node_idx_left_child(current)].priority > h->nodes[node_idx_right_child(current)].priority){
            _heapify_idx_swap(h, node_idx_right_child(current), current);
            current = node_idx_right_child(current);
        }
    }

    return current;
}

Heap *heap_construct(size_t size){
    Heap *h = malloc(sizeof(Heap));
    h->size = 0;
    h->capacity = size;
    h->nodes = calloc(h->capacity, sizeof(HeapNode));
    h->positions = calloc(size, sizeof(int));
    for(int i = 0; i < size; i++){
        h->positions[i] = -1;
    }

    return h;
}

void heap_push(Heap *heap, int node, double priority){
    int nodepos = heap->positions[node];
    //se ja existir, atualiza o valor e ajeita o heap (pra cima ou pra baixo)
    if(nodepos != -1){
        if(heap->nodes[nodepos].priority > priority){
            heap->nodes[nodepos].priority = priority;
            _heapify(heap, nodepos);
        }
            
        else if(heap->nodes[nodepos].priority < priority){
            heap->nodes[nodepos].priority = priority;
            _heapify_down(heap, nodepos);
        }
    }

    //se o valor não existir, insere normalmente no final e faz heapify
    HeapNode heapnode;
    heapnode.data = node;
    heapnode.priority = priority;
    heap->nodes[heap->size++] = heapnode;

    //ajeita ele para a posicao certa no heap e salva em new_pos
    int new_pos = _heapify(heap, heap->size - 1);

    //coloca na tabela a nova posicao do node no heap
    heap->positions[node] = new_pos;
}

int heap_empty(Heap *heap){return heap->size == 0;}

void *heap_min(Heap *heap){return heap->nodes[0].data;}

double heap_min_priority(Heap *heap){return heap->nodes[0].priority;}

void *heap_pop(Heap *heap){
    //retira o minimo do heap e seta sua posição como -1
    heap->size--;
    int pop = heap->nodes[0].data;
    heap->positions[pop] = -1;

    //coloca o do final no lugar do minimo e ajeita ele no heap
    heap->nodes[0] = heap->nodes[heap->size];
    _heapify_down(heap, 0);

    return pop;
}

void heap_destroy(Heap *heap){
    free(heap->nodes);
    free(heap);
}
