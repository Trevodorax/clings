#ifndef CLINGS_TYPES_H
#define CLINGS_TYPES_H

#include "stdlib.h"
#include "mocks.h"

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
 * @see new_sized_string_from_str_of_length
 * @see new_sized_string_of_length
 * @see empty_sized_string
 */
typedef struct sized_string_t {
    char * str;
    size_t len;
} sized_string_t;

typedef struct run_kata_result {
    kata_status status;
    union {
        sized_string_t output;
        sized_string_t error;
    };
} run_kata_result_t;


/**
 * @brief Creates a new sized_string_t with the specified length.
 * The string is filled of null character '\0';
 * If the given length is 0, it will allocate the string "\0";
 *
 * @code
 * new_sized_string_of_length(2);
 * // Will return the sized_string_t -> {str: "\0\0\0", len: 2}
 * @endcode
 *
 * @param len The length of the string buffer to allocate
 * @return A sized_string_t with allocated string and specified length
 */
sized_string_t new_sized_string_of_length_with_calloc(size_t len, calloc_f calloc);
#define new_sized_string_of_length(len) new_sized_string_of_length_with_calloc(len, &calloc)

/**
 * @brief Creates a new `sized_string_t` object from a null-terminated string.
 *
 * This function dynamically allocates a new `sized_string_t` struct and initializes it with
 * the content of the provided string (char *). The size of the new `sized_string_t` object is
 * determined by the length of the input string. If the input string is NULL, the function
 * returns a `sized_string_t` object with size 0 and no content. The length does NOT includes the
 * terminating character '\0'.
 *
 * @param string A pointer to the null-terminated string from which to create the `sized_string_t` object.
 *               If this parameter is NULL, a `sized_string_t` object representing an empty string is returned.
 *
 * @return A `sized_string_t` object containing the content of the provided string and its size.
 *         If the input string is NULL, returns a `sized_string_t` object with length 0.
 *
 * @note The returned `sized_string_t` object is dynamically allocated and should be freed
 *       appropriately by the caller to avoid memory leaks with the function @code free_sized_string() @endcode
 *
 * Example Usage:
 * @code
 * char *my_string = "Hello";
 * sized_string_t my_sized_string = new_sized_string_from(my_string);
 * // Now, `my_string` contains the struct {.string = "Hello\0" (allocated), len = 6 }.
 * @endcode
 */
sized_string_t new_sized_string_from(char *string);


/**
 * @brief Clones a `sized_string_t` object.
 *
 * Creates a new `sized_string_t` object that is a duplicate of the input `sized_string_t` object.
 * This function allocates memory for the new `sized_string_t` object and copies the content
 * and length from the original. The clone will have its own memory allocation for the string
 * content, making it independent from the original `sized_string_t` object.
 *
 * @param string A `sized_string_t` object to be cloned. This parameter includes both
 *               the string content (`str`) and its length (`len`).
 *
 * @return A new `sized_string_t` object that is a clone of the input. The returned object
 *         contains a copy of the original string's content and has the same length.
 *
 * @note The returned `sized_string_t` object is dynamically allocated and must be freed
 *       by the caller to prevent memory leaks with the function @code free_sized_string() @endcode
 *
 * Example Usage:
 * @code
 * sized_string_t original = new_sized_string_from("Hello, world!");
 * sized_string_t clone = clone_sized_string(original);
 * @endcode
 */
sized_string_t clone_sized_string(sized_string_t string);


/**
 * @brief Concatenates two `sized_string_t` objects into a new `sized_string_t` object.
 *
 * This function creates a new `sized_string_t` object whose content is the concatenation
 * of the string contents of the first and second input `sized_string_t` objects. The function
 * dynamically allocates memory for the new `sized_string_t` object and its string content.
 * If either of the input strings is empty, the function returns a clone of the
 * other string. If both strings are non-empty, their contents are combined into a new string
 * with a length equal to the sum of their lengths.
 *
 * @param first The first `sized_string_t` object to concatenate.
 * @param second The second `sized_string_t` object to concatenate.
 *
 * @return A new `sized_string_t` object that is the concatenation of the first and second
 *         input strings. If one of the inputs is an empty string, returns a clone of the
 *         non-empty string. The returned object's length is the sum of the lengths of the
 *         two input strings.
 *
 * @note The returned `sized_string_t` object and its string content are dynamically allocated
 *       and must be freed by the caller to prevent memory leaks. The concatenation includes
 *       terminating the new string with a null character (`'\0'`), ensuring it is properly
 *       terminated for use with standard C string functions, though this null terminator is not
 *       included in the length count of the `sized_string_t` object.
 *
 * Example Usage:
 * @code
 * sized_string_t first = { .str = "Hello, ", .len = 7 };
 * sized_string_t second = { .str = "world!", .len = 6 };
 * sized_string_t combined = concat_two_sized_string(first, second);
 * // Now combined equals -> { .str = "Hello, world!\0", .len = 13 };
 * @endcode
 */
sized_string_t concat_two_sized_string(sized_string_t first, sized_string_t second);

/**
 * @brief Create new sized string from a given string(char*) with specified length.
 *
 * This function creates a new `sized_string_t` structure by copying the
 * specified string (char *) with the given length (NOT including
 * the terminating ‘\0’ character). The function allocates memory for
 * the new string. It allocates len + 1 characters and terminates the
 * copied string with a NULL character '\0'.
 *
 * The function copy at most (`len`) characters from src.
 * If src is less than len characters long, the remainder of
 * the sized_string_t.src is filled with ‘\0’ characters.
 *
 * Examples Usage:
 * @code
 * char * str = "Hello";
 * sized_string_t hello_str = new_sized_string_from_str_of_length(str, strlen(str));
 * // Now, `hello_str` contains the copied string "Hello\0" with length 5.
 * @endcode
 *
 * @code
 * new_sized_string_from_str_of_length("abcdef", 3);
 * // Will return -> {str: "abc\0", len: 3}
 * @endcode
 *
 * @code
 * new_sized_string_from_str_of_length("abc", 5);
 * // Will return -> {str: "abc\0\0\0", len: 5}
 * @endcode
 *
 * @param str The string to be copied.
 * @param len The length of the string to be copied. (NOT including the terminating char)
 *
 * @return A sized_string_t with the copied string and its length.
 *
 * @see sized_string_t
 */
sized_string_t new_sized_string_from_str_of_length(char * str, size_t len);

/**
 * @brief Frees the memory allocated for a sized_string_t
 *
 * @param string The sized_string_t to be freed
 */
void free_sized_string(sized_string_t *string);

#endif //CLINGS_TYPES_H
