#include "../../headers/rtt.h"
#include "../../headers/dijkstra.h"
#include <stdlib.h>
#include <float.h>

#define INFINITY DBL_MAX;

struct Rtt{
    double **S_to_C_rtt; // S_to_C_shortest[S][C] = RTT weight from s to c
    double **S_to_M_rtt; // S_to_M_shortest[S][M] = RTT weight from s to m
    double **M_to_C_rtt; // M_to_C_shortest[M][C] = RTT weight from m to c
    size_t n_servers;
    size_t n_clients;
    size_t n_monitors;
};

double **blank_matrix(int n, int m){
    double **matrix = malloc(sizeof(double *) * n);
    for(int i = 0; i < n; i++){
        matrix[i] = malloc(sizeof(double) * m);
    }
    return matrix;
}

void free_matrix(double **matrix, int n){
    for(int i = 0; i < n; i++){
        free(matrix[i]);
    }
    free(matrix);
}

Rtt *rtt_construct(Graph *graph){
    Rtt *rtt = malloc(sizeof(Rtt));
    
    rtt->S_to_C_rtt = blank_matrix(graph_get_num_servers(graph), graph_get_num_clients(graph));
    rtt->S_to_M_rtt = blank_matrix(graph_get_num_servers(graph), graph_get_num_monitors(graph));
    rtt->M_to_C_rtt = blank_matrix(graph_get_num_monitors(graph), graph_get_num_clients(graph));

    rtt->n_servers = graph_get_num_servers(graph);
    rtt->n_clients = graph_get_num_clients(graph);
    rtt->n_monitors = graph_get_num_monitors(graph);

    return rtt;
}

void rtt_destroy(Rtt *rtt){
    free_matrix(rtt->S_to_C_rtt, rtt->n_servers);
    free_matrix(rtt->S_to_M_rtt, rtt->n_servers);
    free_matrix(rtt->M_to_C_rtt, rtt->n_monitors);

    free(rtt);
}

double rtt_weight(int source, int destination, double **dijkstra_matrix){
    return dijkstra_matrix[source][destination] + dijkstra_matrix[destination][source];
}

double rtt_star_weight(int source, int destination, int *monitors, int n_monitors, double **dijkstra_matrix){
    double min = INFINITY;
    for(int i = 0; i < n_monitors; i++){
        int monitor = monitors[i];
        double weight = dijkstra_matrix[source][monitor] + dijkstra_matrix[monitor][destination] + dijkstra_matrix[destination][monitor] + dijkstra_matrix[monitor][source];
        if(min > weight){
            min = weight;
        }
    }
    return min;
}

Rtt *rtt_run(Graph *graph){
    double **vertices_distances = malloc(sizeof(double *) * graph_get_num_vertex(graph));

    for(int i = 0; i < graph_get_num_vertex(graph); i++){
        vertices_distances[i] = dijkstra_algorithm(graph, i);
    }

    Rtt *rtt = rtt_construct(graph);

    for(int i = 0; i < graph_get_num_servers(graph); i++){
        int server = graph_get_server_index(graph, i);
        for(int j = 0; j < graph_get_num_clients(graph); j++){
            int client = graph_get_client_index(graph, j);
            rtt->S_to_C_rtt[i][j] = rtt_weight(server, client, vertices_distances);
        }
        for(int j = 0; j < graph_get_num_monitors(graph); j++){
            int monitor = graph_get_monitor_index(graph, j);
            rtt->S_to_M_rtt[i][j] = rtt_weight(server, monitor, vertices_distances);
        }
    }
    for(int i = 0; i < graph_get_num_monitors(graph); i++){
        int monitor = graph_get_monitor_index(graph, i);
        for(int j = 0; j < graph_get_num_clients(graph); j++){
            int client = graph_get_client_index(graph, j);
            rtt->M_to_C_rtt[i][j] = rtt_weight(monitor, client, vertices_distances);
        }
    }

    for(int i = 0; i < graph_get_num_vertex(graph); i++){
        free(vertices_distances[i]);
    }
    free(vertices_distances);

    return rtt;
}

Rtt *rtt_star_run(Graph *graph){
    double **vertices_distances = malloc(sizeof(double *) * graph_get_num_vertex(graph));

    for(int i = 0; i < graph_get_num_vertex(graph); i++){
        vertices_distances[i] = dijkstra_algorithm(graph, i);
    }

    Rtt *rtt = rtt_construct(graph);

    for(int i = 0; i < graph_get_num_servers(graph); i++){
        int server = graph_get_server_index(graph, i);
        for(int j = 0; j < graph_get_num_clients(graph); j++){
            int client = graph_get_client_index(graph, j);
            rtt->S_to_C_rtt[i][j] = rtt_star_weight(server, client, graph_get_monitors(graph), graph_get_num_monitors(graph), vertices_distances);
        }
        for(int j = 0; j < graph_get_num_monitors(graph); j++){
            int monitor = graph_get_monitor_index(graph, j);
            rtt->S_to_M_rtt[i][j] = rtt_star_weight(server, monitor, graph_get_monitors(graph), graph_get_num_monitors(graph), vertices_distances);
        }
    }
    for(int i = 0; i < graph_get_num_monitors(graph); i++){
        int monitor = graph_get_monitor_index(graph, i);
        for(int j = 0; j < graph_get_num_clients(graph); j++){
            int client = graph_get_client_index(graph, j);
            rtt->M_to_C_rtt[i][j] = rtt_star_weight(monitor, client, graph_get_monitors(graph), graph_get_num_monitors(graph), vertices_distances);
        }
    }

    for(int i = 0; i < graph_get_num_vertex(graph); i++){
        free(vertices_distances[i]);
    }
    free(vertices_distances);

    return rtt;
}

Rtt *rtt_star_from_rtt(Rtt *rtt, Graph *graph){
    Rtt *rtt_star = rtt_construct(graph);

    for(int i = 0; i < rtt->n_servers; i++){
        for(int j = 0; j < rtt->n_clients; j++){
            int flag = 0;
            for(int k = 0; k < rtt->n_monitors; k++){
                if(!flag){
                    rtt_star->S_to_C_rtt[i][j] = rtt->S_to_M_rtt[i][k] + rtt->M_to_C_rtt[k][j];
                    flag = 1;
                }
                else{
                    double weight = rtt->S_to_M_rtt[i][k] + rtt->M_to_C_rtt[k][j];
                    if(rtt_star->S_to_C_rtt[i][j] > weight){
                        rtt_star->S_to_C_rtt[i][j] = weight;
                    }
                }
            }
        }
    }

    return rtt_star;
}

void rtt_print(Rtt *rtt, Graph *graph){
    printf("S_to_C_rtt\n");
    for(int i = 0; i < rtt->n_servers; i++){
        printf("%d: ", graph_get_server_index(graph, i));
        for(int j = 0; j < rtt->n_clients; j++){
            printf("to %d: %lf ", graph_get_client_index(graph, j), rtt->S_to_C_rtt[i][j]);
        }
        printf("\n");
    }
    printf("S_to_M_rtt\n");
    for(int i = 0; i < rtt->n_servers; i++){
        printf("%d: ", graph_get_server_index(graph, i));
        for(int j = 0; j < rtt->n_monitors; j++){
            printf("to %d: %lf ", graph_get_monitor_index(graph, j), rtt->S_to_M_rtt[i][j]);
        }
        printf("\n");
    }
    printf("M_to_C_rtt\n");
    for(int i = 0; i < rtt->n_monitors; i++){
        printf("%d: ", graph_get_monitor_index(graph, i));
        for(int j = 0; j < rtt->n_clients; j++){
            printf("to %d: %lf ", graph_get_client_index(graph, j), rtt->M_to_C_rtt[i][j]);
        }
        printf("\n");
    }
}

double **rtt_get_S_to_C_rtt(Rtt *rtt){
    return rtt->S_to_C_rtt;
}


