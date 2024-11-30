#include <stdio.h>

#include <application_settings.h>
#include <csv_parser.h>
#include <result_generator.h>
#include <time.h>
#include <csv_output.h>
#include <qsort.h>

#include <application_test.h>

long long current_time_in_ms() {
    struct timespec ts;
    clock_gettime(1, &ts); // Use CLOCK_MONOTONIC to avoid time jumps
    return (ts.tv_sec * 1000LL) + (ts.tv_nsec / 1000000); // Convert to milliseconds
}

bool isTest = false;

int main(int argc, char *argv[]) {
    if (isTest) {
        test_global();
        return 0;
    }

    long long start_time = current_time_in_ms();

    ApplicationSettings *settings = parse_application_settings(argc, argv);
    if (settings == NULL) {
        printf("Invalid settings\n");
        printf("Usage: %s <filename> <station_type> <consumer_type> [power_plant]\n", argv[0]);
        return 2;
    }

    if (!validate_application_settings(settings)) {
        printf("Invalid settings\n");
        printf("Usage: %s <filename> <station_type> <consumer_type> [power_plant]\n", argv[0]);
        free_application_settings(settings);
        return 3;
    }

    print_application_settings(settings);
    long long setting_time = current_time_in_ms();
    printf("Settings elapsed time: %lld ms\n", setting_time - start_time);

    StationNode *node = process_csv_file(settings);
    if (node == NULL) {
        printf("Error processing file\n");
        free_application_settings(settings);
        return 4;
    }

    long long processing_time = current_time_in_ms();
    printf("Processing elapsed time: %lld ms\n", processing_time - setting_time);

    int count = 0;
    StationResult **results = collect_results(node, &count);
    if (results == NULL) {
        printf("Error collecting results\n");
        free_application_settings(settings);
        free_station_node(node);
        return 5;
    }

    printf("Results:\n");
    print_station_result(results, count);

    long long collect_time = current_time_in_ms();
    printf("Collect elapsed time: %lld ms\n", collect_time - processing_time);

    // sort_by_capacity(results, count);
    qsort_by_capacity(results, count);
    printf("Results sorted by capacity:\n");
    print_station_result(results, count);
    long long sort_time = current_time_in_ms();
    printf("Sort elapsed time: %lld ms\n", sort_time - collect_time);

    char *filename = generate_output_filename(settings);
    if (filename == NULL) {
        printf("Error generating filename\n");
        free_application_settings(settings);
        for (int i = 0; i < count; i++) {
            free_station_result(results[i]);
        }
        free(results);
        free_station_node(node);
        return 6;
    }

    write_csv(filename, results, count);
    long long write_time = current_time_in_ms();
    printf("Write elapsed time: %lld ms\n", write_time - sort_time);

    if (settings->station_type == STATION_LV && settings->consumer_type == CONSUMER_ALL) {
        printf("Case of LV and all consumers generating minmax file\n");
        qsort_by_load(results, count);
        long long load_sort_time = current_time_in_ms();
        printf("Load sort elapsed time: %lld ms\n", load_sort_time - write_time);

        char *minmax_filename = generate_minmax_output_filename(settings);
        if (minmax_filename == NULL) {
            printf("Error generating minmax filename\n");
            free_application_settings(settings);
            for (int i = 0; i < count; i++) {
                free_station_result(results[i]);
            }
            free(results);
            free_station_node(node);
            free(filename);
            return 7;
        }

        write_min_max_csv(minmax_filename, results, count);
        long long minmax_write_time = current_time_in_ms();
        printf("Minmax write elapsed time: %lld ms\n", minmax_write_time - load_sort_time);
    }

    for (int i = 0; i < count; i++) {
        free_station_result(results[i]);
    }
    free(results);
    free(filename);

    free_station_node(node);
    free_application_settings(settings);

    long long end_time = current_time_in_ms();

    //clear terminal
    printf("\033[H\033[J");
    printf("Resume:\n");
    printf("Settings elapsed time: %lld ms\n", setting_time - start_time);
    printf("Processing elapsed time: %lld ms\n", processing_time - setting_time);
    printf("Collect elapsed time: %lld ms\n", collect_time - processing_time);
    printf("Sort elapsed time: %lld ms\n", sort_time - collect_time);
    printf("Elapsed time: %lld ms\n", end_time - start_time);

    return 0;
}
