#include <csv_output.h>

#include <stdio.h>

void write_csv(char *filename, StationResult **results, int count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    fprintf(file, "station_id,capacity,load,ratio\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%lld,%lld,%.2f\n", results[i]->station_id, results[i]->capacity, results[i]->load, results[i]->ratio);
    }

    fclose(file);
}

