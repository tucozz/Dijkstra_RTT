#include "../headers/graph.h"

typedef struct Rtt Rtt;

// returns a blank rtt, that contais all the distances between the nodes
Rtt *rtt_construct(Graph *graph);

// destroy the rtt
void rtt_destroy(Rtt *rtt);

// returns the rtt distance between the source and the destination
double rtt_weight(Graph *graph, int source, int destination);

// returns the rtt* distance between the source and the destination
double rtt_star_weight(Graph *graph, int source, int destination);

// fills a blank rtt with the original rtt algorithm
Rtt *rtt_run(Graph *graph);

// fills a blank rtt with the rtt* algorithm
Rtt *rtt_star_run(Graph *graph);
