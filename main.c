#include "headers/input_reader.h"
#include "headers/output_writer.h"
#include "headers/graph.h"
#include "headers/heap.h"
#include "headers/dijkstra.h"
#include "headers/rtt.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: ./trab1 <arquivo_input> <aquivo_output>\n");
        return 1;
    }

    // Le o input
    Graph *graph = graph_read(argv[1]);

    Rtt *rtt = rtt_run(graph);
    Rtt *rtt2 = rtt_star_run(graph);

    // TODO: Imprimir o arquivo de saida de modo correto
    // Modo correto: Três colunas. Uma para a origem, uma para o destino e uma para a razao entre custos RTT e RTT*
    // A estrutura RTT já tem os valores de RTT e RTT* para cada par de vértices. Basta calcular a razão e imprimir

    double **S_to_C_rtt = rtt_get_S_to_C_rtt(rtt);
    double **S_to_C_rtt_star = rtt_get_S_to_C_rtt(rtt2);

    // printf("%lf" , S_to_C_rtt[0][0] / S_to_C_rtt_star[0][0]);

    // PRINT PARA DEBUG:
    // TODO: Alguns valores estão dando infinito. Verificar o que está acontecendo
    // provavelmente é o dijkstra em algum caso específico, mas verificar isso aí.
    for (int i = 0; i < graph_get_num_servers(graph); i++)
    {
        for (int j = 0; j < graph_get_num_clients(graph); j++)
        {
            //printf("%lf %lf\n", S_to_C_rtt[i][j], S_to_C_rtt_star[i][j]);
            double rtt_ratio =  S_to_C_rtt_star[i][j]/S_to_C_rtt[i][j];
            printf("%d %d %lf\n", graph_get_server_index(graph, i), graph_get_client_index(graph, j), rtt_ratio);
        }
    }

    // Escreve o output
    // write_output_in_file_(argv[2]);

    // Libera a memoria
    graph_destroy(graph);
    rtt_destroy(rtt);
    rtt_destroy(rtt2);

    return 0;
}