#include <stdio.h> 
#include <time.h>
#include "../lib/common.c"

#ifndef TEST_COMMON
#define TEST_COMMON

struct results {
    float time;
    size_t comparisions;
};

typedef struct results (* test_func_t)(char**, size_t);

#endif // TEST_COMMON
