#include "common.c"
#include "../lib/tree.c"

struct results test_tree (char** data, size_t size) {
    struct results res;
    tree_node_t* tree = NULL;

    for (size_t i = 0; i < size; ++i) {
        tree = insert_t(tree, data[i]);
    }

    comparisions_count = 0;
    clock_t start = clock();

    tree = delete_t(tree, data[rand() % size]);

    clock_t end = clock();    
    res.time = end - start;
    res.comparisions = comparisions_count;

    return res;
};