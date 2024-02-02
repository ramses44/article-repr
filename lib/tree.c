#include <stdlib.h> 
#include "common.c"

typedef struct Node {
    elem_t data;
    struct Node* left;
    struct Node* right;
} tree_node_t;

tree_node_t* insert_t(tree_node_t* root, elem_t data) {
    if (!root) {
        tree_node_t* new_node = malloc(sizeof(*new_node));
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;

        return new_node;
    }

    if (compare(data, root->data) < 0) {
        root->left = insert_t(root->left, data);
    } else {
        root->right = insert_t(root->right, data);
    }

    return root;
}

tree_node_t* delete_t(tree_node_t* root, elem_t data) {
    if (!root) {
        return root;
    }

    if (compare(data, root->data) == 0) {
        if (!root->left) {
            tree_node_t* r = root->right;
            free(root);
            return r;
        }   

        tree_node_t* tmp = root;     

        while (tmp->left->left) {
            tmp = tmp->left;
        }

        root->data = tmp->left->data;

        tree_node_t* r = tmp->left->right;
        free(tmp->left);
        tmp->left = r;
    } else if (compare(data, root->data) < 0) {
        root->left = delete_t(root->left, data);
    } else {
        root->right = delete_t(root->right, data);
    }

    return root;
}
