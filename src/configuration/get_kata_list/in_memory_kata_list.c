#include "get_kata_list.h"
#include "katas/katas.h"
#include "string.h"

const static kata_t KATA_LIST[] = {
        {.name={.str="intro"}, .path={.str="katas/intro.c"}},
        {.name={.str="success"}, .path={.str="katas/success.c"}},
        {.name={.str="compilation error"}, .path={.str="katas/compilation_error.c"}},
        {.name={.str="run error"}, .path={.str="katas/run_error.c"}},
        {.name={.str="test error"}, .path={.str="katas/test_error.c"}},
};

kata_t kata_t_of(const char* name, const char* path) {
    return (kata_t) {
            .name = copy_str_to_sized_string((char*)name, strlen(name)),
            .path = copy_str_to_sized_string((char*)path, strlen(path)),
    };
}

kata_list_fetch_result_t get_kata_list(void) {
    kata_list_t kata_list = {.katas = NULL, .len = 0};

    const int8_t kata_list_size = sizeof(KATA_LIST) / sizeof(kata_t);
    for (int i = 0; i < kata_list_size; i++) {
        const kata_t kata = KATA_LIST[i];
        push_kata_in_list(kata_t_of(kata.name.str, kata.path.str), &kata_list);
    }

    return (kata_list_fetch_result_t) {
            .success = true,
            .kata_list = kata_list,
    };
}
