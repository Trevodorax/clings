#include <string.h>
#include "types.h"
#include "stdarg.h"

sized_string_t new_sized_string_of_length_with_calloc(size_t len, calloc_f calloc) {
    sized_string_t string;

    string.str = (char *) (*calloc)( // call the parameter function pointer calloc (see calloc_f)
            len + 1, // including the terminating null character '\0'.
            sizeof(char)
            );
    if (string.str) {
        string.len = len;
    } else {
        string.len = 0;
    }
    return string;
}

sized_string_t new_sized_string_from_str_of_length(char *str, size_t len) {
    if(!str) {
        return new_sized_string_of_length(0);
    }
    sized_string_t string = new_sized_string_of_length(len);
    if (!string.str) {
        return string;
    }
    strncpy(string.str, str, len);
    string.str[len] = '\0';
    return string;
}

sized_string_t new_sized_string_from(char *string) {
    if (!string) {
        return new_sized_string_of_length(0);
    }
    return new_sized_string_from_str_of_length(
            string,
            strlen(string)
    );
}

sized_string_t clone_sized_string(sized_string_t string) {
    return new_sized_string_from_str_of_length(string.str, string.len);
}

sized_string_t concat_two_sized_string(sized_string_t first, sized_string_t second) {
    if (!first.str || first.len == 0) {
        return clone_sized_string(second);
    }
    if (!second.str || second.len == 0) {
        return clone_sized_string(first);
    }
    sized_string_t string = new_sized_string_of_length(first.len + second.len);
    strncpy(stpncpy(string.str, first.str, first.len), second.str, second.len);
    string.str[string.len] = '\0';
    return string;
}

void free_sized_string(sized_string_t *string) {
    if (string->str) {
        free(string->str);
        string->str = NULL;
    }
    string->len = 0;
}

void free_several_sized_strings_(sized_string_t * string, ...) {
    va_list args;
    sized_string_t * current;

    va_start(args, string);
    for(current = string; current != NULL; current = va_arg(args, sized_string_t*)) {
        free_sized_string(current);
    }
    va_end(args);
}


