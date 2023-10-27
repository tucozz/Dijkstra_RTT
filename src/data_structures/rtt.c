#include ../headers/rtt.h;

struct Rtt{
    double **S_to_C_rtt; // S_to_C_shortest[S][C] = RTT weight from s to c
    double **S_to_M_rtt; // S_to_M_shortest[S][M] = RTT weight from s to m
    double **M_to_C_rtt; // M_to_C_shortest[M][C] = RTT weight from m to c
};

double **blank_matrix(int n, int m){
    double **matrix = malloc(sizeof(double *) * n);
    for(int i = 0; i < n; i++){
        matrix[i] = malloc(sizeof(double) * m);
        for(int j = 0; j < m; j++){
            matrix[i][j] = INFINITY;
        }
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
    
    rtt->S_to_C_rtt = blank_matrix(graph_get_n_servers(graph), graph_get_n_clients(graph));
    rtt->S_to_M_rtt = blank_matrix(graph_get_n_servers(graph), graph_get_n_monitors(graph));
    rtt->M_to_C_rtt = blank_matrix(graph_get_n_monitors(graph), graph_get_n_clients(graph));

    return rtt;
}

void rtt_destroy(Rtt *rtt){
    free_matrix(rtt->S_to_C_rtt, graph_get_n_servers(graph), graph_get_n_clients(graph));
    free_matrix(rtt->S_to_M_rtt, graph_get_n_servers(graph), graph_get_n_monitors(graph));
    free_matrix(rtt->M_to_C_rtt, graph_get_n_monitors(graph), graph_get_n_clients(graph));

    free(rtt);
}

double rtt_weight(Graph *graph, int source, int destination){
    return dijkstra_weight(graph, source, destination) + dijkstra_weight(graph, destination, source);
}

double rtt_star_weight(Graph *graph, int source, int destination){
    double min = INFINITY;
    for(int i = 0; i < graph_get_n_monitors(graph); i++){
        int monitor = graph_get_monitor_index(graph, i);
        dijkstra_weight(graph, source, monitor) + dijkstra_weight(graph, monitor, destination);
        if(min > weight){
            min = weight;
        }
    }
    return min;
}

Rtt *rtt_run(Graph *graph){
    Rtt *rtt = rtt_construct(graph);
    for(int i = 0; i < graph_get_n_servers(graph); i++){
        int server = graph_get_server_index(graph, i);
        for(int j = 0; j < graph_get_n_clients(graph); j++){
            int client = graph_get_client_index(graph, j);
            rtt->S_to_C_rtt[i][j] = rtt_weight(graph, server, client);
        }
        for(int j = 0; j < graph_get_n_monitors(graph); j++){
            int monitor = graph_get_monitor_index(graph, j);
            rtt->S_to_M_rtt[i][j] = rtt_weight(graph, server, monitor);
        }
    }
    for(int i = 0; i < graph_get_n_monitors(graph); i++){
        int monitor = graph_get_monitor_index(graph, i);
        for(int j = 0; j < graph_get_n_clients(graph); j++){
            int client = graph_get_client_index(graph, j);
            rtt->M_to_C_rtt[i][j] = rtt_weight(graph, monitor, client);
        }
    }
    return rtt;
}

Rtt *rtt_star_run(Graph *graph){
    Rtt *rtt = rtt_construct(graph);
    for(int i = 0; i < graph_get_n_servers(graph); i++){
        int server = graph_get_server_index(graph, i);
        for(int j = 0; j < graph_get_n_clients(graph); j++){
            int client = graph_get_client_index(graph, j);
            rtt->S_to_C_rtt[i][j] = rtt_star_weight(graph, server, client);
        }
        for(int j = 0; j < graph_get_n_monitors(graph); j++){
            int monitor = graph_get_monitor_index(graph, j);
            rtt->S_to_M_rtt[i][j] = rtt_star_weight(graph, server, monitor);
        }
    }
    for(int i = 0; i < graph_get_n_monitors(graph); i++){
        int monitor = graph_get_monitor_index(graph, i);
        for(int j = 0; j < graph_get_n_clients(graph); j++){
            int client = graph_get_client_index(graph, j);
            rtt->M_to_C_rtt[i][j] = rtt_star_weight(graph, monitor, client);
        }
    }
    return rtt;
}



