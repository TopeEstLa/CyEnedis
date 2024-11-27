#include <result_generator.h>

#include <stdlib.h>

StationResult* create_station_result(StationNode* node) {
    if (node == NULL) return NULL;

    StationResult* result = malloc(sizeof(StationResult));
    if (result == NULL) return NULL;

    result->station_id = node->id;
    result->capacity = node->capacity;
    result->load = node->load;
    result->ratio = (double) (node->load / node->capacity);

    return result;
}
