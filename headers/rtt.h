#include "../headers/graph.h"

typedef struct Rtt Rtt;

// returns a blank rtt, that contais all the distances between the nodes
Rtt *rtt_construct(Graph *graph);

// destroy the rtt
void rtt_destroy(Rtt *rtt);

// returns the rtt distance between the source and the destination
double rtt_weight(int source, int destination, double **dijkstra_matrix);

// returns the rtt* distance between the source and the destination
double rtt_star_weight(int source, int destination, int *monitors, int n_monitors, double **dijkstra_matrix);

// returns a rtt* from a rtt
Rtt *rtt_star_from_rtt(Rtt *rtt, Graph *graph);

// fills a blank rtt with the original rtt algorithm
Rtt *rtt_run(Graph *graph);

// fills a blank rtt with the rtt* algorithm
Rtt *rtt_star_run(Graph *graph);

// prints the rtt
void rtt_print(Rtt *rtt, Graph *graph);

// returns the S_to_C_rtt matrix
double **rtt_get_S_to_C_rtt(Rtt *rtt);