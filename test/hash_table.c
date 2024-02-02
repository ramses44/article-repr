#include "common.c"
#include "../lib/hash_table.c"

struct results test_hash_table(char** data, size_t size) {
    struct results res;
    hash_table* ht = create_ht(size);

    for (size_t i = 0; i < size; ++i) {
        insert_ht(ht, data[i]);
    }

    comparisions_count = 0;
    clock_t start = clock();

    delete_ht(ht, data[rand() % size]);

    clock_t end = clock();    
    res.time = end - start;
    res.comparisions = comparisions_count;

    return res;
};