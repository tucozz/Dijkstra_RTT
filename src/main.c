#include "../headers/input_reader.h"
#include "../headers/output_writer.h"

int main(int argc, char **argv)
{
    graph_read(argv[1]);
    // printf("%d", argc);
    write_output_in_file_(argv[2]);

    float k = 2 % 32;
    printf("%f", k);

    return 0;
}