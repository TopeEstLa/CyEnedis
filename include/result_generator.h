#ifndef RESULT_GENERATOR_H
#define RESULT_GENERATOR_H

#include <avl.h>
#include <list.h>

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
    long long load;
    double ratio;
} StationResult;


/**
 * @brief Create a new station result from a station node
 * @param node The station node
 * @return The new station result
 */
StationResult* create_station_result(StationNode* node);

/**
 * @brief Free a station result
 * @param result The station result to free
 */
void free_station_result(StationResult* result);

/**
 * @brief Print a station result to the console
 * @param result The station result to print
 * @param count The number of results
 */
void print_station_result(StationResult** result, int count);

/**
 * @brief Facade function to collect results from an AVL tree and transform them into a tab
 * @param root The root of the AVL tree
 * @param count The number of results
 * @return The array of results
 */
StationResult** collect_results(StationNode* root, int* count);

/**
 * @brief Using an List (from CDataType) to collect results from an AVL tree
 * @param node the node to add to the list
 * @param list the list to add to
 */
void collect_results_helper(StationNode *node, List *list);

/**
 * Bubble sort to sort the results by capacity
 * @param results
 * @param count
 * @return
 */
StationResult** sort_by_capacity(StationResult** results, int count);


#endif //RESULT_GENERATOR_H
