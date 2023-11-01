#include "headers/input_reader.h"
#include "headers/output_writer.h"
#include "headers/graph.h"
#include "headers/heap.h"
#include "headers/dijkstra.h"
#include "headers/rtt.h"

int compare_rtt_ratio(const void *a, const void *b)
{
    rtt_ratio *rtt_ratio_a = (rtt_ratio *)a;
    rtt_ratio *rtt_ratio_b = (rtt_ratio *)b;

    //compare first by ratio. If ratio is equal, compare by server index. If server index is equal, compare by client index
    if(rtt_ratio_a->rtt_ratio != rtt_ratio_b->rtt_ratio)
        return (rtt_ratio_a->rtt_ratio < rtt_ratio_b->rtt_ratio) ? -1 : 1;

    if(rtt_ratio_a->server != rtt_ratio_b->server)
        return (rtt_ratio_a->server < rtt_ratio_b->server) ? -1 : 1;

    if(rtt_ratio_a->client != rtt_ratio_b->client)
        return (rtt_ratio_a->client < rtt_ratio_b->client) ? -1 : 1;

    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: ./trab1 <arquivo_input> <aquivo_output>\n");
        return 1;
    }

    // Le o input e guarda em uma variavel do tipo Graph
    Graph *graph = graph_read(argv[1]);

    // Não tem necessidade de calcular o RTT* do zero, mas a função está descrita no arquivo rtt.c
    Rtt *rtt = rtt_run(graph);
    Rtt *rtt2 = rtt_star_from_rtt(rtt, graph);

    // Separa os valores de RTT* e RTT uteis (S_to_C)
    double **S_to_C_rtt = rtt_get_S_to_C_rtt(rtt);
    double **S_to_C_rtt_star = rtt_get_S_to_C_rtt(rtt2);
    rtt_ratio *rtt_ratio_arr = malloc(sizeof(rtt_ratio) * graph_get_num_servers(graph) * graph_get_num_clients(graph));

    // Calcula a razao entre RTT* e RTT e guarda em um vetor de rtt_ratio (é util para ordenar)
    for (int i = 0; i < graph_get_num_servers(graph); i++)
    {
        for (int j = 0; j < graph_get_num_clients(graph); j++)
        {
            rtt_ratio_arr[i * graph_get_num_clients(graph) + j].server = graph_get_server_index(graph, i);
            rtt_ratio_arr[i * graph_get_num_clients(graph) + j].client = graph_get_client_index(graph, j);
            rtt_ratio_arr[i * graph_get_num_clients(graph) + j].rtt_ratio = S_to_C_rtt_star[i][j] / S_to_C_rtt[i][j];

        }
    }

    // ordena o vetor de rtt_ratio
    qsort(rtt_ratio_arr, graph_get_num_servers(graph) * graph_get_num_clients(graph), sizeof(rtt_ratio), compare_rtt_ratio);

    // Escreve o output
    write_output_in_file_(argv[2], rtt_ratio_arr, graph_get_num_servers(graph) * graph_get_num_clients(graph));

    // Libera a memoria
    graph_destroy(graph);
    rtt_destroy(rtt);
    rtt_destroy(rtt2);
    free(rtt_ratio_arr);

    return 0;
}