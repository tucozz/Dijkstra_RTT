#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdio.h>

typedef struct Heap Heap;

int heap_min(Heap *heap);
int heap_pop(Heap *heap);
int heap_empty(Heap *heap);
void heap_debug(Heap *heap);
void heap_destroy(Heap *heap);
int get_heap_size(Heap *heap);
Heap *heap_construct(size_t size);
double heap_min_priority(Heap *heap);
void heap_push(Heap *heap, int data, double priority);

#endif
