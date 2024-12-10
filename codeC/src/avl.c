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
    node->eq = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

StationNode *insert_station_node(StationNode *root, int *h, int id, long long capacity, long long load) {
    if (root == NULL) {
        *h = 1;
        return create_station_node(id, capacity, load);
    }

    if (id < root->id) {
        root->left = insert_station_node(root->left, h, id, capacity, load);
        *h = -*h;
    } else if (id > root->id) {
        root->right = insert_station_node(root->right, h, id, capacity, load);
    } else {
        *h = 0;
        //root->capacity = capacity;
        //root->load = load;
        return root;
    }

    if (*h != 0) {
        root->eq += *h;
        root = equalize_avl(root);
        *h = (root->eq == 0) ? 0 : 1;
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

int get_node_count(StationNode *node) {
    if (node == NULL) return 0;

    return 1 + get_node_count(node->left) + get_node_count(node->right);
}

StationNode *rotate_left(StationNode *node) {
    StationNode *new_root = node->right;
    StationNode *temp = new_root->left;

    int eq_root = node->eq;
    int eq_new_root = new_root->eq;

    new_root->left = node;
    node->right = temp;

    node->eq = eq_root - max(eq_new_root, 0) - 1;
    new_root->eq = min3(eq_root - 2, eq_root + eq_new_root - 2, eq_new_root - 1);

    return new_root;
}

StationNode *rotate_right(StationNode *node) {
    StationNode *new_root = node->left;
    StationNode *temp = new_root->right;

    int eq_root = node->eq;
    int eq_new_root = new_root->eq;

    new_root->right = node;
    node->left = temp;

    node->eq = eq_root - min(eq_new_root, 0) + 1;
    new_root->eq = max3(eq_root + 2, eq_root + eq_new_root + 2, eq_new_root + 1);

    return new_root;
}

StationNode *double_rotate_left(StationNode *node) {
    node->right = rotate_right(node->right);
    return rotate_left(node);
}

StationNode *double_rotate_right(StationNode *node) {
    node->left = rotate_left(node->left);
    return rotate_right(node);
}


bool is_avl(StationNode *root) {
    if (root == NULL) return true;

//    int balance = balance_factor(root);
    int balance = root->eq;
    if (balance > MAX_TOLERANCE || balance < MIN_TOLERANCE) return false;

    return is_avl(root->left) && is_avl(root->right);
}

StationNode *equalize_avl(StationNode *root) {
    if (root == NULL) return NULL;

    if (root->eq >= 2) {
        //check is left is null
        if (root->right == NULL) {
            return root;
        }

        if (root->right->eq >= 0) {
            return rotate_left(root);
        } else {
            return double_rotate_left(root);
        }
    } else if (root->eq <= -2) {
        if (root->left == NULL) {
            return root;
        }

        if (root->left->eq <= 0) {
            return rotate_right(root);
        } else {
            return double_rotate_right(root);
        }
    }

    return root;
}