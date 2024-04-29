#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "execution.h"

run_kata_result_t run_kata_result_of(kata_t kata, const char * message_to_fill, kata_status status) {
    size_t full_message_length = strlen(message_to_fill) + kata.path.len;
    if(full_message_length > MAX_OUTPUT_SIZE) {
        full_message_length = MAX_OUTPUT_SIZE;
    }
    sized_string_t error_message = new_sized_string_of_length(full_message_length);
    snprintf(error_message.str, full_message_length, message_to_fill, kata.path);
    run_kata_result_t result = {
            .status = status,
            .error = error_message,
    };
    return result;
}

run_kata_result_t kata_not_found(kata_t kata) {
    return run_kata_result_of(kata, "Kata in file [%s] not found.", KATA_ERROR);
}

run_kata_result_t compilation_failed(kata_t kata) {
    return run_kata_result_of(kata, "Compilation of kata %s failed.", KATA_COMPILATION_FAILURE);
}

run_kata_result_t execution_failed(kata_t kata) {
    return run_kata_result_of(kata, "Execution of kata %s failed.", KATA_EXECUTION_FAILURE);
}

run_kata_result_t execution_success(sized_string_t output) {
    run_kata_result_t result = {
            .status = KATA_SUCCESS,
            .output = output,
    };
    return result;
}

run_kata_result_t run_kata(const kata_t kata) {

    // check if file exists
    FILE* file = fopen(kata.path.str, "r");
    if(file == NULL) {
        return kata_not_found(kata);
    }
    fclose(file);

    // Create compile command
    printf("Compiling %s\n", kata.path.str);
    char compile_command[MAX_PATH_LENGTH];
    snprintf(compile_command, MAX_PATH_LENGTH, COMPILE_COMMAND, kata.path.str);

    // Compile kata file
    if (system(compile_command) != EXIT_SUCCESS) {
        return compilation_failed(kata);
    }

    // Run compiled kata file
    FILE *fp = popen(RUN_COMMAND, "r");
    if (fp == NULL) {
        return execution_failed(kata);
    }

    // Read output to result_buffer
    sized_string_t output = new_sized_string_of_length(MAX_PATH_LENGTH);
    fread(output.str, output.len, 1, fp);

    // Check execution status
    if (pclose(fp) != EXIT_SUCCESS) {
        return execution_failed(kata);
    }

    return execution_success(output);
}
