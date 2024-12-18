#include <application_test.h>

#include <stdio.h>
#include <stdlib.h>

int test_global() {
    printf("Starting tests\n");
    ApplicationSettings *settingsParser = test_settings_parser();
    if (settingsParser == NULL) {
        printf("[Test] Settings parser failed\n");
        return 1;
    }
    printf("[Test] Settings parser passed\n");

    StationNode *node = test_avl_build(settingsParser);
    if (node == NULL) {
        printf("[Test] AVL build failed\n");
        return 1;
    }
    printf("[Test] AVL build passed\n");

    int count = 0;

    StationResult **result = test_output(node, &count);
    if (result == NULL) {
        printf("[Test] Output failed\n");
        return 1;
    }
    printf("[Test] Output passed\n");


    StationResult **sorted_result = test_qsort(result, count);
    if (sorted_result == NULL) {
        printf("[Test] Qsort failed\n");
        return 1;
    }
    printf("[Test] Qsort passed\n");
    printf("All tests passed\n");
    printf("Cleaning up\n");

    for (int i = 0; i < count; i++) {
        free_station_result(sorted_result[i]);
    }
    free(sorted_result);
    free_station_node(node);
    free_application_settings(settingsParser);
    printf("Clean up done\n");
    return 0;
}

ApplicationSettings *test_settings_parser() {
    //Testing normal case
    char *argv[] = {"test", "test-files/test-data.csv", "lv", "all"};
    ApplicationSettings *settings = parse_application_settings(4, argv);
    assert(settings != NULL);

    assert(strcmp(settings->filename, "test-files/test-data.csv") == 0);
    assert(strcmp(settings->delimiter, DEFAULT_DELIMITER) == 0);
    assert(settings->power_plant == -1);
    assert(settings->station_type == STATION_LV);
    assert(settings->consumer_type == CONSUMER_ALL);
    assert(validate_application_settings(settings));
    // free_application_settings(settings);

    char *argv1[] = {"test", "test.csv", "hvb", "comp"};
    ApplicationSettings *settings1 = parse_application_settings(4, argv1);
    assert(settings1 != NULL);
    assert(strcmp(settings1->filename, "test.csv") == 0);
    assert(strcmp(settings1->delimiter, DEFAULT_DELIMITER) == 0);
    assert(settings1->power_plant == -1);
    assert(settings1->station_type == STATION_HVB);
    assert(settings1->consumer_type == CONSUMER_COMPANY);
    assert(validate_application_settings(settings1));

    free_application_settings(settings1);

    char *argv6[] = {"test", "test.csv", "hva", "indiv"};
    ApplicationSettings *settings6 = parse_application_settings(4, argv6);
    assert(settings6 != NULL);
    assert(strcmp(settings6->filename, "test.csv") == 0);
    assert(strcmp(settings6->delimiter, DEFAULT_DELIMITER) == 0);
    assert(settings6->power_plant == -1);
    assert(settings6->station_type == STATION_HVA);
    assert(settings6->consumer_type == CONSUMER_INDIVIDUAL);
    assert(!validate_application_settings(settings6));

    free_application_settings(settings6);

    //Testing special power plant case
    char *argv2[] = {"test", "test.csv", "lv", "all", "1"};
    ApplicationSettings *settings2 = parse_application_settings(5, argv2);
    assert(settings2 != NULL);
    assert(strcmp(settings2->filename, "test.csv") == 0);
    assert(strcmp(settings2->delimiter, DEFAULT_DELIMITER) == 0);
    assert(settings2->power_plant == 1);
    assert(settings2->station_type == STATION_LV);
    assert(settings2->consumer_type == CONSUMER_ALL);

    free_application_settings(settings2);

    //Testing invalid case
    char *argv3[] = {"test", "test.csv", "lv", "all", "1", "2"};
    ApplicationSettings *settings3 = parse_application_settings(6, argv3);
    assert(settings3 == NULL);

    char *argv4[] = {"test", "test.csv", "lv", "all", "a"};
    ApplicationSettings *settings4 = parse_application_settings(5, argv4);
    assert(settings4 == NULL);

    char *argv5[] = {"test.csv", "lv", "all", "1"};
    ApplicationSettings *settings5 = parse_application_settings(4, argv5);
    assert(settings5 == NULL);

    return settings;
}

StationNode *test_avl_build(ApplicationSettings *settings) {
    if (settings == NULL) {
        return NULL;
    }

    StationNode *root = NULL;

    root = process_csv_file(settings);
    assert(root != NULL);

    //check if data is correct
    StationNode *node_to_find = get_station_node(root, 1);
    assert(node_to_find != NULL);
    assert(node_to_find->load == 171359043);
    assert(node_to_find->capacity == 241999040);
    assert(is_avl(root));

    root = equalize_avl(root);
    assert(is_avl(root));

    return root;
}

StationResult **test_output(StationNode *node, int *count) {
    if (node == NULL) {
        return NULL;
    }

    StationResult **result = collect_results(node, count);
    assert(result != NULL);

    for (int i = 0; i < *count; i++) {
        assert(result[i] != NULL);
    }

    for (int i = 0; i < *count - 1; i++) {
        assert(result[i]->station_id <= result[i + 1]->station_id);
    }

    return result;
}

StationResult **test_qsort(StationResult **result, int count) {
    qsort_by_capacity(result, count);

    for (int i = 0; i < count - 1; i++) {
        assert(result[i]->capacity <= result[i + 1]->capacity);
    }

    qsort_by_load(result, count);
    for (int i = 0; i < count - 1; i++) {
        assert(result[i]->load <= result[i + 1]->load);
    }

    qsort_by_ratio(result, count);
    for (int i = 0; i < count - 1; i++) {
        assert(result[i]->ratio >= result[i + 1]->ratio);
    }

    return result;
}

bool as_test_argument(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-test") == 0) {
            return true;
        }
    }
    return false;
}