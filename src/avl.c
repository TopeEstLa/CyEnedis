#include <avl.h>

#include <stdlib.h>
#include <maths.h>


StationNode *create_station_node(Station *station) {
    StationNode *node = (StationNode *)malloc(sizeof(StationNode));
    node->station = station;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

StationNode *insert_station_node(StationNode *root, Station *station) {
    if (root == NULL) return create_station_node(station);

    if (station->id < root->station->id) {
        root->left = insert_station_node(root->left, station);
    } else if (station->id > root->station->id) {
        root->right = insert_station_node(root->right, station);
    } else {
        return root;
    }

    update_height(root);

    int balance = balance_factor(root);

    if (balance > MAX_TOLERANCE && station->id < root->left->station->id) {
        return rotate_right(root);
    }

    if (balance < MIN_TOLERANCE && station->id > root->right->station->id) {
        return rotate_left(root);
    }

    if (balance > MAX_TOLERANCE && station->id > root->left->station->id) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    if (balance < MIN_TOLERANCE && station->id < root->right->station->id) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

StationNode *delete_station_node(StationNode *root, long id) {

}

int get_height(StationNode *node) {
    if (node == NULL) return 0;

    return node->height;
}

void update_height(StationNode *node) {
    if (node == NULL) return;

    node->height = 1 + max(get_height(node->left), get_height(node->right));
}

int balance_factor(StationNode *node) {
    if (node == NULL) return 0;

    return get_height(node->left) - get_height(node->right);
}

StationNode *rotate_left(StationNode *node) {
    StationNode *new_root = node->right;
    StationNode *temp = new_root->left;

    new_root->left = node;
    node->right = temp;

    update_height(node);
    update_height(new_root);

    return new_root;
}

StationNode *rotate_right(StationNode *node) {
    StationNode *new_root = node->left;
    StationNode *temp = new_root->right;

    new_root->right = node;
    node->left = temp;

    update_height(node);
    update_height(new_root);

    return new_root;
}

