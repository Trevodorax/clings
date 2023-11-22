#ifndef CLINGS_TYPES_H
#define CLINGS_TYPES_H

#include <stddef.h>
#include <stdlib.h>

typedef enum {
    KATA_SUCCESS, // the kata is done
    KATA_COMPILATION_FAILURE, // error at compile time
    KATA_EXECUTION_FAILURE, // error at run time
    KATA_TEST_FAILURE, // at least one unit test has failed
    KATA_ERROR // there was an error (file not found, etc.)
} kata_status;


/**
 * @brief Represents a sized string with length information.
 *
 * The `sized_string_t` structure combines a character pointer (`str`) pointing
 * to the actual string content and a size_t (`len`) representing the length
 * of the string. This structure is commonly used to handle strings along with
 * their length, allowing for efficient string manipulation and storage.
 *
 * Example Usage:
 * @code
 * sized_string_t my_string = {.str = "Hello, World!", .len = 13};
 * // Now, `my_string` represents a string with content "Hello, World!" and length 13.
 * @endcode
 *
 * @see copy_str_to_sized_string
 * @see new_sized_string
 * @see empty_sized_string
 */
typedef struct sized_string_t {
    char * str;
    size_t len;
} sized_string_t;

/**
 * @brief Creates a new sized_string_t with the specified length
 *
 * @param len The length of the string buffer to allocate
 * @return A sized_string_t with allocated string and specified length
 */
sized_string_t new_sized_string(size_t len);

/**
 * @brief Copies a given string to a sized string.
 *
 * This function creates a new `sized_string_t` structure by copying the
 * specified string (`str`) with the given length (`len`) (including
 * the terminating ‘\0’ character). The function allocates memory for
 * the new string.
 *
 * The function copy at most (`len`) characters from src.
 * If src is less than len characters long, the remainder of
 * the sized_string_t.src is filled with ‘\0’ characters.
 *
 * Example Usage:
 * @code
 * char * str = "Hello";
 * sized_string_t hello_str = copy_str_to_sized_string(str, strlen(str));
 * // Now, `hello_str` contains the copied string "Hello" with length 5.
 * @endcode
 *
 * @param str The string to be copied.
 * @param len The length of the string to be copied.
 *
 * @return A sized_string_t with the copied string and its length.
 *
 * @see sized_string_t
 */
sized_string_t copy_str_to_sized_string(char * str, size_t len);


/**
 * @brief Creates an empty sized string.
 *
 * This function returns a `sized_string_t` structure representing an empty
 * string. The structure has a null pointer for the string content (`str`)
 * and a length (`len`) of 0.
 *
 * @return A `sized_string_t` structure with a null string pointer and length 0.
 *
 * @see sized_string_t
 */
sized_string_t empty_sized_string(void);

/**
 * @brief Frees the memory allocated for a sized_string_t
 *
 * @param string The sized_string_t to be freed
 */
void free_sized_string(sized_string_t *string);

#endif //CLINGS_TYPES_H
