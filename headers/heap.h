#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdio.h>

typedef struct Heap Heap;

Heap *heap_construct(size_t size);
void heap_push(Heap *heap, int data, double priority);
int heap_empty(Heap *heap);
int heap_min(Heap *heap);
double heap_min_priority(Heap *heap);
int heap_pop(Heap *heap);
void heap_debug(Heap *heap);
void heap_destroy(Heap *heap);

#endif
