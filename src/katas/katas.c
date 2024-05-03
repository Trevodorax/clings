#include <stdio.h>
#include "katas.h"


void free_kata_list(kata_list_t *kata_list) {
    if (kata_list->katas == NULL) return;
    for (size_t i = 0; i < kata_list->len; i++) {
        free_kata(&kata_list->katas[i]);
    }
    kata_list->katas = NULL;
    kata_list->len = 0;
}

void free_kata(kata_t *kata) {
    if (kata) {
        free_sized_string(&kata->name);
        free_sized_string(&kata->path);
    }
}

void push_kata_in_list_with_realloc(kata_t kata, kata_list_t *list, realloc_f realloc) {
    if (!list->katas) {
        list->len = 0;
    }

    kata_t *reallocated = (*realloc)( // call the parameter function pointer realloc (see realloc_f)
            list->katas,
            (list->len + 1) * sizeof(kata_t)
    );
    if (reallocated == NULL) {
        return;
    }
    list->len++;
    list->katas = reallocated;
    list->katas[list->len - 1] = kata;
}

bool kata_file_exists_with_fopen(const kata_t kata, fopen_f fopen) {
    FILE* file = (*fopen)(kata.path.str, "r"); // call the parameter function pointer fopen (see fopen_f)
    if(file == NULL) {
    return false;
    }
    fclose(file);
    return true;
}
