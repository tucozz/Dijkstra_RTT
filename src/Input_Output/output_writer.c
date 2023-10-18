#include "../../headers/output_writer.h"

void write_output_in_file_(char *name)
{
    // char *filepath = malloc(sizeof(char) * 1000);
    // strcpy(filepath, MST_OUTPUT_FOLDER);
    // strcat(filepath, name);
    // strcat(filepath, ".mst");

    FILE *file = fopen(name, "w");

    fprintf(file, "hehe arquivo de saida");
    fclose(file);
    // free(filepath);
}