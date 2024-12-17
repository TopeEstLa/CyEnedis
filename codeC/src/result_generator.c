#include <result_generator.h>

#include <stdlib.h>
#include <stdio.h>

StationResult *create_station_result(StationNode *node) {
    if (node == NULL) return NULL;

    StationResult *result = malloc(sizeof(StationResult));
    if (result == NULL) return NULL;

    result->station_id = node->id;
    result->capacity = node->capacity;
    result->load = node->load;
    long long rate = node->capacity - node->load;
    result->ratio = llabs(rate);

    return result;
}

void print_station_result(StationResult **result, int count) {
    if (result == NULL) return;

    for (int i = 0; i < count; i++) {
        printf("%d: %lld %lld %lld\n", result[i]->station_id, result[i]->capacity, result[i]->load, result[i]->ratio);
    }
}

void free_station_result(StationResult *result) {
    if (result == NULL) return;
    free(result);
}

void collect_results_helper(StationNode *node, StationResult **list, int *index) {
    if (node == NULL) return;

    collect_results_helper(node->left, list, index);

    StationResult *result = create_station_result(node);
    if (result == NULL) return;

    list[*index] = result;
    (*index)++;

    collect_results_helper(node->right, list, index);
}

StationResult **collect_results(StationNode *root, int *count) {
    if (root == NULL) return NULL;
    *count = 0;
    int node_count = get_node_count(root);

    StationResult **results = malloc((node_count + 1) * sizeof(StationResult *));
    if (results == NULL) return NULL;

    int index = 0;
    collect_results_helper(root, results, &index);

    *count = index;

    return results;
}

StationResult **sort_by_capacity(StationResult **results, int count) {
    if (results == NULL) return NULL;

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (results[j]->capacity > results[j + 1]->capacity) {
                StationResult *temp = results[j];
                results[j] = results[j + 1];
                results[j + 1] = temp;
            }
        }
    }

    return results;
}