#include <result_generator.h>

#include <stdlib.h>
#include <list.h>
#include <stdio.h>

StationResult *create_station_result(StationNode *node) {
    if (node == NULL) return NULL;

    StationResult *result = malloc(sizeof(StationResult));
    if (result == NULL) return NULL;

    result->station_id = node->id;
    result->capacity = node->capacity;
    result->load = node->load;
    result->ratio = (double) ((double) node->load / (double) node->capacity);

    return result;
}

void print_station_result(StationResult** result, int count) {
    if (result == NULL) return;

    for (int i = 0; i < count; i++) {
        printf("%d: %lld %lld %.2f\n", result[i]->station_id, result[i]->capacity, result[i]->load, result[i]->ratio);
    }
}

void free_station_result(StationResult* result) {
    if (result == NULL) return;
    free(result);
}

void collect_results_helper(StationNode *node, List *list) {
    if (node == NULL) return;

    collect_results_helper(node->left, list);

    StationResult *result = create_station_result(node);
    if (result == NULL) return;
    append(list, result);

    collect_results_helper(node->right, list);
}

StationResult **collect_results(StationNode *root, int *count) {
    if (root == NULL) return NULL;
    *count = 0;

    List *list = createList();
    if (list == NULL) return NULL;
    collect_results_helper(root, list);

    StationResult **results = malloc(list->size * sizeof(StationResult *));
    if (results == NULL) return NULL;

    ListNode *current = list->head;
    for (int i = 0; i < list->size; i++) {
        results[i] = current->data;
        current = current->next;
    }

    *count = list->size;
    freeList(list);

    return results;
}

StationResult** sort_by_capacity(StationResult** results, int count) {
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