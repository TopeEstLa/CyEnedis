#include <csv_output.h>

#include <stdio.h>
#include <stdlib.h>
#include <qsort.h>

void write_csv(ConsumerType consumerType, char *filename, StationResult **results, int count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    switch (consumerType) {
        case CONSUMER_COMPANY:
            fprintf(file, "station_id:capacity:load (company):ratio\n");
            break;
        case CONSUMER_INDIVIDUAL:
            fprintf(file, "station_id:capacity:load (indiv):ratio\n");
            break;
        case CONSUMER_ALL:
            fprintf(file, "station_id:capacity:load (all):ratio\n");
            break;
        case CONSUMER_INVALID:
        default:
            fprintf(file, "station_id:capacity:load:ratio\n");
            break;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d:%lld:%lld:%lld\n", results[i]->station_id, results[i]->capacity, results[i]->load,
                results[i]->ratio);
    }

    fclose(file);
}

void write_min_max_csv(ConsumerType consumerType, char *filename, StationResult **results, int count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }


    if (count < FIST_MAX + LAST_MIN) {
        //Not enough data to write min/max just write all
        qsort_by_ratio(results, count);
        write_csv(consumerType, filename, results, count);
        return;
    }

    qsort_by_load(results, count);

    int minmax_count = 0;
    StationResult** minmax_results = malloc((FIST_MAX + LAST_MIN + 1) * sizeof(StationResult*));
    if (minmax_results == NULL) {
        exit(8);
    }

    for (int i = 0; i < FIST_MAX; i++) {
        minmax_results[minmax_count] = results[i];
        minmax_count++;
    }

    for (int i = count - LAST_MIN; i < count; i++) {
        minmax_results[minmax_count] = results[i];
        minmax_count++;
    }

    qsort_by_ratio(minmax_results, minmax_count);


    switch (consumerType) {
        case CONSUMER_COMPANY:
            fprintf(file, "station_id:capacity:load (company):ratio\n");
            break;
        case CONSUMER_INDIVIDUAL:
            fprintf(file, "station_id:capacity:load (indiv):ratio\n");
            break;
        case CONSUMER_ALL:
            fprintf(file, "station_id:capacity:load (all):ratio\n");
            break;
        case CONSUMER_INVALID:
        default:
            fprintf(file, "station_id:capacity:load:ratio\n");
            break;
    }

    for (int i = 0; i < minmax_count; i++) {
        fprintf(file, "%d:%lld:%lld:%lld\n", minmax_results[i]->station_id, minmax_results[i]->capacity,
                minmax_results[i]->load, minmax_results[i]->ratio);
    }

    free(minmax_results);
    fclose(file);
}