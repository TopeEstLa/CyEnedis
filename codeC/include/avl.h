#ifndef AVL_H
#define AVL_H

#include <stdbool.h>

#define MIN_TOLERANCE (-1)
#define MAX_TOLERANCE 1

/**
 * @brief AVL tree node for stations.
 * @param id id of the station corresponding to the node.
 * @param capacity The capacity of the station.
 * @param load The load of the station.
 * @param height The height of the node.
 * @param left The left child of the node.
 * @param right The right child of the node.
 */
typedef struct station_node {
    int id;
    long long capacity;
    long long load;
    int height;
    struct station_node *left, *right;
} StationNode;

/**
 * @brief Creates a new station node.
 * @param station The station struct.
 * @return The new station node (can be a root or a leaf).
 */
StationNode *create_station_node(int id, long long capacity, long long load);

/**
 * @brief Inserts a station node to the AVL tree.
 * @param root The root of the AVL tree.
 * @param station The station struct.
 * @return The new root of the AVL tree.
 */
StationNode *insert_station_node(StationNode *root, int id, long long capacity, long long load);

/**
 * @brief Frees a station node and its children.
 * @param node The node to free.
 */
void free_station_node(StationNode *node);

/**
 * @brief Get a station node from the AVL tree.
 * @param root The root of the AVL tree.
 * @param id The id of the station.
 * @return The station node or NULL if not found.
 */
StationNode *get_station_node(StationNode *root, int id);

/**
 * @brief Pretty print the AVL tree.
 * @param node The root of the AVL tree.
 * @param depth The depth of the node.
 */
void pretty_print_avl(StationNode *node, int depth);

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
 * @brief Get the count of the nodes in the tree.
 * @param node The root.
 * @retur The count of the nodes.
 */
int get_node_count(StationNode *node);

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

/**
 * @brief Check if the tree is AVL.
 * @param root The root of the tree.
 * @return True if the tree is AVL.
 */
bool is_avl(StationNode *root);

/**
 * @brief Equalize the AVL tree.
 * @param root The root of the tree.
 * @return The new root of the tree.
 */
StationNode* equalize_avl(StationNode* root);

#endif //AVL_H
