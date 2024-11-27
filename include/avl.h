#ifndef AVL_H
#define AVL_H

#include <station.h>

#define MIN_TOLERANCE -1
#define MAX_TOLERANCE 1

/**
 * @brief AVL tree node for stations.
 * @param station The station struct.
 * @param height The height of the node.
 * @param left The left child of the node.
 * @param right The right child of the node.
 */
typedef struct station_node {
    int id;
    long capacity;
    long load;
    int height;
    struct station_node *left, *right;
} StationNode;

/**
 * @brief Creates a new station node.
 * @param station The station struct.
 * @return The new station node (can be a root or a leaf).
 */
StationNode *create_station_node(int id, long capacity, long load);

/**
 * @brief Inserts a station node to the AVL tree.
 * @param root The root of the AVL tree.
 * @param station The station struct.
 * @return The new root of the AVL tree.
 */
StationNode *insert_station_node(StationNode *root, int id, long capacity, long load);

/**
 * @brief Get a station node from the AVL tree.
 * @param root The root of the AVL tree.
 * @param id The id of the station.
 * @return The station node or NULL if not found.
 */
StationNode *get_station_node(StationNode *root, long id);

/**
 * @brief Get the height of the node.
 * @param node The node.
 * @return The height of the node.
 */
int get_height(StationNode *node);

/**
 * @brief update the height of the node.
 * @param node The node.
 */
void update_height(StationNode *node);

/**
 * @brief Get the balance factor of the node.
 * @param node The node
 * @return
 */
int balance_factor(StationNode *node);

/**
 * @brief Made a left rotation.
 * @param node The node
 * @return The new root of the tree.
 */
StationNode *rotate_left(StationNode *node);

/**
 * @brief Made a right rotation.
 * @param node The node
 * @return The new root of the tree.
 */
StationNode *rotate_right(StationNode *node);


#endif //AVL_H
