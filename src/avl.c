#include <avl.h>

#include <stdlib.h>
#include <maths.h>
#include <stdio.h>

StationNode *create_station_node(int id, long long capacity, long long load) {
    StationNode *node = malloc(sizeof(StationNode));
    if (node == NULL) return NULL;

    node->id = id;
    node->capacity = capacity;
    node->load = load;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

StationNode *insert_station_node(StationNode *root, int id, long long capacity, long long load) {
    if (root == NULL) return create_station_node(id, capacity, load);

    if (id < root->id) {
        root->left = insert_station_node(root->left, id, capacity, load);
    } else if (id > root->id) {
        root->right = insert_station_node(root->right, id, capacity, load);
    } else {
        //No duplicates allowed
        return root;
    }

    update_height(root);

    int balance = balance_factor(root);

    if (balance > MAX_TOLERANCE && id < root->left->id) {
        return rotate_right(root);
    }

    if (balance < MIN_TOLERANCE && id > root->right->id) {
        return rotate_left(root);
    }

    if (balance > MAX_TOLERANCE && id > root->left->id) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    if (balance < MIN_TOLERANCE && id < root->right->id) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

void free_station_node(StationNode *node) {
    if (node == NULL) return;

    free_station_node(node->left);
    free_station_node(node->right);
    free(node);
}

StationNode *get_station_node(StationNode *root, int id) {
    if (root == NULL) return NULL;

    if (id < root->id) {
        return get_station_node(root->left, id);
    } else if (id > root->id) {
        return get_station_node(root->right, id);
    } else {
        return root;
    }
}

void pretty_print_avl(StationNode *node, int depth) {
    if (node == NULL) return;

    pretty_print_avl(node->right, depth + 1);

    for (int i = 0; i < depth; i++) printf("    ");
    printf("%d (%lld, %lld)\n", node->id, node->capacity, node->load);

    pretty_print_avl(node->left, depth + 1);
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

