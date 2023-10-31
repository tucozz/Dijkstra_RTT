#include "../../headers/output_writer.h"
#include "../../headers/rtt.h"

void write_output_in_file_(char *name, rtt_ratio *rtt_ratio_arr, int size)
{

    FILE *file = fopen(name, "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%d %d %.16lf\n", rtt_ratio_arr[i].server, rtt_ratio_arr[i].client, rtt_ratio_arr[i].rtt_ratio);
    }

    fclose(file);

}