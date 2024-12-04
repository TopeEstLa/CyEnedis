#include <stdio.h>

#include <application_settings.h>
#include <csv_parser.h>
#include <result_generator.h>
#include <csv_output.h>
#include <qsort.h>
#include <stdlib.h>
#include <pthread.h>

#include <application_test.h>
#include <benchmark.h>
#include <waiting_scene.h>

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

    pthread_t tid;
    pthread_create(&tid, NULL, draw_waiting_scene, NULL);


    mark_benchmark_start();
    ApplicationSettings *settings = parse_application_settings(argc, argv);
    if (settings == NULL) {
        pthread_cancel(tid);
        return 2;
    }

    if (!validate_application_settings(settings)) {
        pthread_cancel(tid);
        return 3;
    }

    mark_setting_time();

    StationNode *node = process_csv_file(settings);
    if (node == NULL) {
        pthread_cancel(tid);
        return 4;
    }

    mark_build_time();

    int count = 0;
    StationResult **results = collect_results(node, &count);
    if (results == NULL) {
        pthread_cancel(tid);
        return 5;
    }

    mark_collect_time();

    free_station_node(node);

    qsort_by_capacity(results, count);
    mark_sort_time();

    char *filename = generate_output_filename(settings);
    if (filename == NULL) {
        pthread_cancel(tid);
        return 6;
    }

    write_csv(filename, results, count);
    mark_write_time();

    if (settings->station_type == STATION_LV && settings->consumer_type == CONSUMER_ALL) {
        qsort_by_load(results, count);

        char *minmax_filename = generate_minmax_output_filename(settings);
        if (minmax_filename == NULL) {
            pthread_cancel(tid);
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
    pthread_cancel(tid);

    mark_benchmark_end();
    benchmark_result();
    return 0;
}
