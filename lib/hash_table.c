#include <stdlib.h>
#include <string.h>
#include "common.c"

typedef struct node {
    elem_t data;
    struct node* next;
} node_t;

typedef node_t list_t;
typedef size_t(* hash_func_t)(elem_t, size_t);

typedef struct {
    list_t** data;
    size_t buckets_count;
    hash_func_t hash_func;
} hash_table;

list_t* push(list_t* head, elem_t data) {
    if (!head) {
        head = malloc(sizeof(*head));
        head->data = data;
        head->next = NULL;
    } else {
        head->next = push(head->next, data);
    }

    return head;
}

list_t* pop(list_t* head, elem_t data) {
    if (!head) {
        return NULL;
    }

    if (compare(data, head->data) == 0) {
        list_t* tmp = head->next;
        free(head);
        return tmp;
    } 

    head->next = pop(head->next, data);

    return head;
}

size_t hash_func(elem_t val, size_t mod) {  // simple hash-function for string
    if (!mod) {
        mod = 1024;
    }

    size_t res = 0;

    while (*val) {
        res += *val * 256ull;
        res = res % mod;
        ++val;
    }

    return res;
}

hash_table* create_ht(size_t buckets_count) {
    if (buckets_count < 1) {
        buckets_count = 1;
    }

    hash_table* res = malloc(sizeof(*res));

    res->buckets_count = buckets_count;
    res->hash_func = hash_func;
    res->data = calloc(buckets_count, sizeof(void*));
    memset(res->data, 0, sizeof(res->data));
    
    return res;
}

void insert_ht(hash_table* ht, elem_t data) {
    size_t index = ht->hash_func(data, ht->buckets_count);

    ht->data[index] = push(ht->data[index], data);
}

void delete_ht(hash_table* ht, elem_t data) {
    size_t index = ht->hash_func(data, ht->buckets_count);

    ht->data[index] = pop(ht->data[index], data);
}
