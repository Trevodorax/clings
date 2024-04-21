#ifndef CLINGS_KATAS_H
#define CLINGS_KATAS_H

#include "types/types.h"
#include "stdbool.h"


/**
 * @brief Represents a kata with name and path information.
 *
 * The `kata_t` structure is used to represent a kata, which consists of a
 * `sized_string_t` for the kata's name (`name`), another `sized_string_t`
 * for the kata's path (`path`) and a boolean representing if it is
 * done or not done.
 *
 * @see sized_string_t
 * @see free_kata
 */
typedef struct kata {
    sized_string_t name;
    sized_string_t path;
    bool is_done;
} kata_t;


/**
 * @brief Represents a list of kata structures.
 *
 * The `kata_list_t` structure is used to represent a list of `kata_t` structures.
 * It includes a pointer to an array of `kata_t` structures (`katas`) and a `size_t`
 * (`len`) indicating the length of the array.
 *
 * Example Usage:
 * @code
 * kata_list_t my_kata_list =  ... ;
 * for (size_t i = 0; i < my_kata_list.len; ++i) {
 *     // Access each kata in the list: my_kata_list.katas[i]...
 * }
 * // Remember to free the memory when done: free_kata_list(&my_kata_list);
 * @endcode
 *
 * @see kata_t
 * @see free_kata_list
 * @see push_kata_in_list
 */
typedef struct kata_list {
    kata_t *katas;
    size_t len;
} kata_list_t;

/**
 * @brief Represents the result of fetching a kata list.
 *
 * The `kata_list_fetch_result_t` structure is used to represent the result
 * of fetching a kata list. It contains a boolean `success` field indicating
 * whether the fetching was successful. In case of success, the structure includes
 * a `kata_list_t` union member representing the parsed kata list. In case of
 * failure, it includes an `error_message` union member containing an error message.
 *
 * Example Usage:
 * @code
 * kata_list_fetch_result_t result = ...
 * if (result.success) {
 *     // Parsing was successful, use result.kata_list...
 *     free_kata_list(&result.kata_list);
 * } else {
 *     // Parsing failed, handle the error with result.error_message...
 * }
 * @endcode
 *
 * @see kata_list_t
 * @see kata_list_parsing_result_t
 * @see free_kata_list
 */
typedef struct kata_list_fetch_result {
    bool success;
    union {
        kata_list_t kata_list;
        const char *error_message;
    };
} kata_list_fetch_result_t;


/**
 * @brief Frees the memory allocated for a kata structure.
 *
 * This function deallocates the memory allocated for the `sized_string_t`
 * members (`name` and `path`) within a given `kata_t` structure.
 *
 * @param kata The kata structure whose memory will be freed.
 *
 * @see kata_t
 * @see sized_string_t
 * @see free_sized_string
 */
void free_kata(kata_t *kata);

/**
 * @brief Frees a `kata_list_t` structure.
 *
 * This function frees the memory allocated for a given `kata_list_t` structure,
 * including the memory allocated for each kata within the list.
 * This function should be called when the `kata_list_t` structure is no longer
 * needed.
 * The pointer to the kata array (kata_t *) is set to NULL after been freed.
 *
 * Example Usage:
 * @code
 * kata_list_t my_kata_list = ... ;
 * free_kata_list(&my_kata_list);
 * assert(my_kata_list.katas == NULL);
 * @endcode
 *
 * @param kata_list The `kata_list_t` structure to be freed.
 *
 * @see kata_list_t
 * @see push_kata_in_list
 */
void free_kata_list(kata_list_t *kata_list);


/**
 * @brief Adds a kata to a kata list.
 *
 * This function adds a given `kata_t` structure to the specified `kata_list_t`
 * by increasing the length of the list, reallocating memory, and appending the
 * new kata. If memory allocation fails, an error message is printed to stderr,
 * and the program exits with a failure status.
 *
 * Example Usage:
 * @code
 * kata_t my_kata =  ... ;
 * kata_list_t my_kata_list = ... ;
 * push_kata_in_list(my_kata, &my_kata_list);
 * // Now, `my_kata_list` contains the newly added kata.
 * @endcode
 *
 * @param kata The kata to be added to the list.
 * @param list The kata list to which the kata will be added.
 *
 * @see kata_t
 * @see kata_list_t
 * @see free_kata_list
 */
void push_kata_in_list(kata_t kata, kata_list_t *list);

#endif //CLINGS_KATAS_H
