#include <stdio.h>
#include "katas.h"


void free_kata_list(kata_list_t *kata_list) {
    if(kata_list->katas == NULL) return;
    for (size_t i = 0; i < kata_list->len; i++) {
        free_kata(&kata_list->katas[i]);
    }
    kata_list->katas = NULL;
}

void free_kata(kata_t *kata) {
    if(kata) {
        free_sized_string(&kata->name);
        free_sized_string(&kata->path);
    }
}

void push_kata_in_list(kata_t kata, kata_list_t *list) {
    list->len++;
    kata_t * reallocated = (kata_t *) realloc(list->katas, list->len * sizeof(kata_t));
    if(reallocated == NULL) {
        fprintf(stderr, "Failed to allocate memory for kata list.");
        free_kata_list(list);
        exit(EXIT_FAILURE);
    }
    list->katas = reallocated;
    list->katas[list->len - 1] = kata;
}

kata_t no_kata(void) {
    return (kata_t) {
            .name = empty_sized_string(),
            .path = empty_sized_string()
    };
}

