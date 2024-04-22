#include <stdio.h>
#include <string.h>
#include "get_kata_list.h"
#include "katas/katas.h"

typedef struct kata_file {
        const char* name;
        const char* directory;
} kata_file_t;

static const kata_file_t KATA_NAME_LIST[] = {
        { .name = "intro", .directory = "00_intro/"},
        { .name = "variables 1", .directory = "01_variables/"},
        { .name = "variables 2", .directory = "01_variables/"},
        { .name = "variables 3", .directory = "01_variables/"},
};

const char* KATAS_BASE_PATH = "katas/";

const char* KATA_NOT_DONE_COMMENT = "// I AM NOT DONE";

sized_string_t kata_path_from_directory_and_name(sized_string_t directory, sized_string_t kata_name);

kata_t kata_of(sized_string_t name, sized_string_t directory);

sized_string_t c_file_name_of(sized_string_t name);

sized_string_t clean_string_to_file_name(sized_string_t string);

bool is_kata_done(sized_string_t path);

kata_list_fetch_result_t get_kata_list(void) {
    kata_list_t kata_list = {.katas = NULL, .len = 0};

    const size_t kata_list_size = sizeof(KATA_NAME_LIST) / sizeof(const kata_file_t);
    for (size_t i = 0; i < kata_list_size; i++) {
        kata_file_t kata_file = KATA_NAME_LIST[i];
        sized_string_t name = new_sized_string_from((char *) kata_file.name);
        sized_string_t directory = new_sized_string_from((char *) kata_file.directory);

        push_kata_in_list(kata_of(name, directory), &kata_list);

        free_sized_string(&directory);
    }

    return (kata_list_fetch_result_t) {
            .success = true,
            .kata_list = kata_list,
    };
}

kata_t kata_of(sized_string_t name, sized_string_t directory) {
    sized_string_t path = kata_path_from_directory_and_name(directory, name);
    return (kata_t) {
            .name = name,
            .path = path,
            .is_done = is_kata_done(path)
    };
}

sized_string_t kata_path_from_directory_and_name(sized_string_t directory, sized_string_t kata_name) {
    sized_string_t base_path = new_sized_string_from((char*) KATAS_BASE_PATH);
    sized_string_t c_file_name = c_file_name_of(kata_name);
    sized_string_t directory_and_c_file = concat_two_sized_string(directory, c_file_name);

    sized_string_t full_path = concat_two_sized_string(base_path, directory_and_c_file);

    free_sized_string(&base_path);
    free_sized_string(&c_file_name);
    free_sized_string(&directory_and_c_file);
    return full_path;
}

sized_string_t c_file_name_of(sized_string_t kata_name) {
    if(kata_name.len == 0) {
        return new_sized_string_from("_.c");
    }
    sized_string_t cleaned_file_name = clean_string_to_file_name(kata_name);
    sized_string_t extension = new_sized_string_from(".c");

    sized_string_t name_with_extension = concat_two_sized_string(cleaned_file_name, extension);

    free_sized_string(&cleaned_file_name);
    free_sized_string(&extension);
    return name_with_extension;
}

sized_string_t clean_string_to_file_name(sized_string_t string) {
    const sized_string_t cleaned = clone_sized_string(string);
    for(size_t i = 0; i < string.len; i++) {
        if(cleaned.str[i] == ' ') {
            cleaned.str[i] = '_';
        }
    }
    return cleaned;
}

bool is_kata_done(sized_string_t path) {
    FILE* kata_file = fopen(path.str, "r");
    if(kata_file == NULL) {
        return true; // file not found, marked as done => not executed
    }
    size_t comment_length = strlen(KATA_NOT_DONE_COMMENT);
    sized_string_t line = new_sized_string_of_length(comment_length);
    bool is_done = true; // by default true if the comment not found
    while(fgets(line.str, (int) comment_length + 1, kata_file)) {
        line.str[strcspn(line.str, "\n")] = '\0';
        bool contains_not_done_comment = strncmp(line.str, KATA_NOT_DONE_COMMENT, comment_length) == 0;
        if (contains_not_done_comment) {
            is_done = false;
            break;
        }
    }
    free_sized_string(&line);
    fclose(kata_file);
    return is_done;
}
