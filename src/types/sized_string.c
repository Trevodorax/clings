#include <string.h>
#include "types.h"

// (3) -> {str: "\0\0\0\0", len: 3}
sized_string_t new_sized_string(size_t len) {
    if(len == 0) {
        return (sized_string_t) {.str = NULL, len = 0};
    }
    sized_string_t string;
    string.str = (char *) calloc(
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

sized_string_t new_sized_string_from_string(char *string) {
    if (!string) {
        return new_sized_string(0);
    }
    return copy_str_to_sized_string(
            string,
            strlen(string)
    );
}

sized_string_t clone_sized_string(sized_string_t string) {
    return copy_str_to_sized_string(string.str, string.len);
}

sized_string_t concat_two_sized_string(sized_string_t first, sized_string_t second) {
    if(first.len == 0) {
        return clone_sized_string(second);
    }
    if(second.len == 0) {
        return clone_sized_string(first);
    }
    sized_string_t string = new_sized_string(first.len + second.len);
    char * end = stpncpy(string.str, first.str, first.len);
    strncpy(end, second.str, second.len);
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

// ("abcdef", 3) -> {str: "abc\0", len: 3}
sized_string_t copy_str_to_sized_string(char *str, size_t len) {
    sized_string_t string = new_sized_string(len);
    if (!string.str) {
        return string;
    }
    strncpy(string.str, str, len);
    string.str[len] = '\0';
    return string;
}


sized_string_t empty_sized_string(void) {
    return (sized_string_t) {
            .str = NULL,
            .len = 0
    };
}
