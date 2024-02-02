#include "common.c"
#include "../lib/avl_tree.c"

struct results test_avl_tree(char** data, size_t size) {
    struct results res;
    balanced_tree_node* tree = NULL;

    for (size_t i = 0; i < size; ++i) {
        tree = insert_at(tree, data[i]);
    }

    comparisions_count = 0;
    clock_t start = clock();

    tree = delete_at(tree, data[rand() % size]);

    clock_t end = clock();    
    res.time = end - start;
    res.comparisions = comparisions_count;

    return res;
};