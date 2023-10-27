#include "headers/input_reader.h"
#include "headers/output_writer.h"
#include "headers/graph.h"
#include "headers/heap.h"

int main(int argc, char **argv)
{
    if(argc != 3){
        printf("Usage: ./trab1 <arquivo_input> <aquivo_output>\n");
        return 1;
    }

    //Le o input
    Graph *graph = graph_read(argv[1]);


    //Escreve o output
    write_output_in_file_(argv[2]);

    return 0;
}