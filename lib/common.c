#include <stddef.h>

#ifndef LIB_COMMON
#define LIB_COMMON


typedef const char* elem_t;

size_t comparisions_count = 0;

int compare(elem_t a, elem_t b) {
    // Compare two srings by symbols.
    // -1 means a < b; 1 means a > b; 0 means a == b

    ++comparisions_count;

    while (*a && *b) {
        if (*a < *b) {
            return -1;
        }
        if (*a > *b) {
            return 1;
        }

        ++a;
        ++b;
    }

    if (*a == *b) {
        return 0;
    }

    return *a ? 1 : -1;
}


#endif // LIB_COMMON