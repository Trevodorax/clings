#include <string.h>
#include "execution_errors.h"


size_t length_or_max_len(size_t size) {
    return size > MAX_OUTPUT_SIZE
        ? MAX_OUTPUT_SIZE
        : size;
}

run_kata_result_t kata_not_found(kata_t kata) {
    const char *message = "Kata in file [%s] not found.";
    size_t message_length = length_or_max_len(strlen(message) + kata.path.len);
    sized_string_t error_message = new_sized_string_of_length(message_length);
    snprintf(error_message.str, message_length, message, kata.path.str);
    return run_kata_result(kata, KATA_ERROR, error_message);
}

run_kata_result_t compilation_failed(kata_t kata, sized_string_t output_error) {
    const char *message = "Compilation of kata [%s] failed : \n%s";
    size_t message_length = length_or_max_len(strlen(message) + kata.path.len + output_error.len);
    sized_string_t error_message = new_sized_string_of_length(message_length);
    snprintf(error_message.str, message_length, message, kata.path.str, output_error.str);
    return run_kata_result(kata, KATA_COMPILATION_FAILURE, error_message);
}

run_kata_result_t execution_failed(kata_t kata, sized_string_t output_error) {
    const char *message = "Execution of kata [%s] failed : \n%s";
    size_t message_length = length_or_max_len(strlen(message) + kata.path.len + output_error.len);
    sized_string_t error_message = new_sized_string_of_length(message_length);
    snprintf(error_message.str, message_length, message, kata.path.str, output_error.str);
    return run_kata_result(kata, KATA_EXECUTION_FAILURE, error_message);
}

run_kata_result_t open_process_failed(kata_t kata, sized_string_t command) {
    const char *message = "Execution of command [%s] failed.";
    size_t message_length = length_or_max_len(strlen(message) + command.len);
    sized_string_t error_message = new_sized_string_of_length(message_length);
    snprintf(error_message.str, message_length, message, command.str);
    return run_kata_result(kata, KATA_EXECUTION_FAILURE, error_message);
}
