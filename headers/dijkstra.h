#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_7

#include "graph.h"

// Returns an array of doubles with the shortest path from the origin to all the other nodes.
// Array[i] = distance from origin to node i.
double *dijkstra_algorithm(Graph *graph, int origin);

#endif