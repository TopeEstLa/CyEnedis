#include <avl.h>

#include <stdlib.h>


StationNode *create_station_node(Station *station) {
    StationNode *node = (StationNode *)malloc(sizeof(StationNode));
    node->station = station;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}