#include <stdlib.h>
#include "common.c"

struct results test_file(char** data, size_t size) {
    struct results res;
    size_t i;

    comparisions_count = 0;
    clock_t start = clock();

    const char* word = data[rand() % size];
    
    for (i = 0; i < size; ++i) {
        if (compare(word, data[i]) == 0) {
            free(data[i]);

            for (size_t j = i; j < size; ++j) {
                data[i] = data[i + 1];
            }

            --size;
            --i;
        }
    }

    clock_t end = clock();    
    res.time = end - start;
    res.comparisions = comparisions_count;

    return res;
};