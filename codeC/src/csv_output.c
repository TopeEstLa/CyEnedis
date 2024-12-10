#include <csv_output.h>

#include <stdio.h>

void write_csv(char *filename, StationResult **results, int count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    fprintf(file, "station_id:capacity:load:ratio\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d:%lld:%lld:%lld\n", results[i]->station_id, results[i]->capacity, results[i]->load, results[i]->ratio);
    }

    fclose(file);
}

void write_min_max_csv(char *filename, StationResult **results, int count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }


    if (count < FIST_MAX + LAST_MIN) {
        //Not enough data to write min/max just write all
        write_csv(filename, results, count);
        return;
    }

    fprintf(file, "station_id:capacity:load:ratio\n");
    for (int i = 0; i < FIST_MAX; i++) {
        fprintf(file, "%d:%lld:%lld:%lld\n", results[i]->station_id, results[i]->capacity, results[i]->load, results[i]->ratio);
    }

    fprintf(file, "...\n");
    for (int i = count - LAST_MIN; i < count; i++) {
        fprintf(file, "%d:%lld:%lld:%lld\n", results[i]->station_id, results[i]->capacity, results[i]->load, results[i]->ratio);
    }

    fclose(file);
}