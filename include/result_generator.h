#ifndef RESULT_GENERATOR_H
#define RESULT_GENERATOR_H

#include <avl.h>

/**
 * @brief Structure for the results of a station
 * @param station_id: The id of the station
 * @param capacity: The capacity of the station
 * @param consumption: The consumption of the station
 * @param ratio: The ratio of consumption to capacity
 */
typedef struct station_result {
    int station_id;
    long long capacity;
    long long consumption;
    double ratio;
} StationResult;


/**
 * @brief Create a new station result from a station node
 * @param node The station node
 * @return The new station result
 */
StationResult* create_station_result(StationNode* node);

/**
 * @brief Collect the results from an AVL tree
 * @param root The root of the AVL tree
 * @param count The number of results
 * @return The array of results
 */
StationResult** collect_results(StationNode* root, int* count);

/**
 * @brief Sort the results by capacity
 * @param results The array of results
 * @param count The number of results
 * @return The sorted array of results
 */
StationResult** sort_results(StationResult** results, int count);


#endif //RESULT_GENERATOR_H
