#include "katas.h"


void free_kata(struct Kata *kata);

void free_kata_list(KataList *kata_list) {
    for (int i = 0; i < kata_list->len; i++) {
        free_kata(&kata_list->katas[i]);
    }
    kata_list->katas = NULL;
}

void free_kata(struct Kata *kata) {
    free_sized_string(&kata->name);
    free_sized_string(&kata->path);
}

void push_kata_in_list(Kata kata, KataList *list) {
    list->len++;
    list->katas = (Kata *) realloc(list->katas, list->len * sizeof(Kata));
    list->katas[list->len - 1] = kata;
}

Kata no_kata() {
    return (Kata) {
            .name = empty_sized_string(),
            .path = empty_sized_string()
    };
}