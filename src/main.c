#include <stdio.h>

#include <application_settings.h>
#include <csv_parser.h>
#include <result_generator.h>
#include <csv_output.h>
#include <qsort.h>
#include <stdlib.h>

#include <application_test.h>
#include <benchmark.h>


bool isTest = false;

int main(int argc, char *argv[]) {
    char* testenv = getenv("RUNNING_TEST");
    if (testenv != NULL && strcmp(testenv, "1") == 0) {
        isTest = true;
    }

    char* benchmarkenv = getenv("RUNNING_BENCHMARK");
    if (benchmarkenv != NULL && strcmp(benchmarkenv, "1") == 0) {
        set_benchmark_enabled(true);
    }

    if (isTest) {
        test_global();
        return 0;
    }

    mark_benchmark_start();
    ApplicationSettings *settings = parse_application_settings(argc, argv);
    if (settings == NULL) {
        printf("Could not parse settings\n");
        printf("Usage: %s <filename> <station_type> <consumer_type> [power_plant]\n", argv[0]);
        return 2;
    }

    if (!validate_application_settings(settings)) {
        printf("Invalid settings\n");
        printf("Usage: %s <filename> <station_type> <consumer_type> [power_plant]\n", argv[0]);
        free_application_settings(settings);
        return 3;
    }

    mark_setting_time();

    StationNode *node = process_csv_file(settings);
    if (node == NULL) {
        printf("Error processing file\n");
        free_application_settings(settings);
        return 4;
    }
    mark_build_time();

    int count = 0;
    StationResult **results = collect_results(node, &count);
    if (results == NULL) {
        printf("Error collecting results\n");
        free_application_settings(settings);
        free_station_node(node);
        return 5;
    }
    mark_collect_time();

    free_station_node(node);

    qsort_by_capacity(results, count);
    mark_sort_time();

    char *filename = generate_output_filename(settings);
    if (filename == NULL) {
        printf("Error generating filename\n");
        free_application_settings(settings);
        for (int i = 0; i < count; i++) {
            free_station_result(results[i]);
        }
        free(results);
        return 6;
    }

    write_csv(filename, results, count);
    mark_write_time();

    if (settings->station_type == STATION_LV && settings->consumer_type == CONSUMER_ALL) {
        printf("Case of LV and all consumers generating minmax file\n");
        qsort_by_load(results, count);

        char *minmax_filename = generate_minmax_output_filename(settings);
        if (minmax_filename == NULL) {
            printf("Error generating minmax filename\n");

            free_application_settings(settings);

            for (int i = 0; i < count; i++) {
                free_station_result(results[i]);
            }

            free(results);
            free(filename);
            return 7;
        }

        write_min_max_csv(minmax_filename, results, count);

        free(minmax_filename);
    }

    for (int i = 0; i < count; i++) {
        free_station_result(results[i]);
    }

    free(results);
    free(filename);

    free_application_settings(settings);

    //clear terminal
    mark_benchmark_end();
    benchmark_result();
    return 0;
}
