#include <stdio.h> 
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "test/tree.c"
#include "test/avl_tree.c"
#include "test/hash_table.c"
#include "test/file.c"

char** str_split(char* a_str, const char a_delim) {
    char** result = 0;
    size_t count = 0;
    char* tmp = a_str;
    char* last_comma = NULL;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    while (*tmp) {
        if (a_delim == *tmp) {
            ++count;
            last_comma = tmp;
        }
        ++tmp;
    }

    count += last_comma < (a_str + strlen(a_str) - 1);
    ++count;

    result = calloc(count, sizeof(char*));

    if (result) {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token) {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        return -1;
    }

    const char* fname = argv[1];
    const char* type = argv[2];

    test_func_t test_func;

    if (compare(type, "tree") == 0) {
        test_func = test_tree;
    } else if (compare(type, "avl-tree") == 0) {
        test_func = test_avl_tree;
    } else if (compare(type, "hash-table") == 0) {
        test_func = test_hash_table;
    } else {
        test_func = test_file;
    }

    FILE* file = fopen(fname, "r");
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* file_data = malloc(fsize + 1);
    fread(file_data, fsize, 1, file);
    fclose(file);

    file_data[fsize] = 0;

    char** splitted = str_split(file_data, ' ');

    size_t length;
    for (length = 0; splitted[length]; ++length);

    struct results res = test_func(splitted, length);

    free(splitted);
    free(file_data);
    
    printf("Time: %f \nComps: %d\n", res.time, res.comparisions);
}