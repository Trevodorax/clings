#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "execution.h"

kata_status run_kata(const kata_t kata, sized_string_t result_buffer) {
    char compile_command[MAX_PATH_LENGTH];

    // check if file exists
    FILE* file = fopen(kata.path.str, "r");
    if(file == NULL) {
        strncpy(result_buffer.str, "File not found", result_buffer.len);
        return KATA_ERROR;
    }
    fclose(file);

    // Create compile command
    printf("Compiling %s\n", kata.path.str);
    snprintf(compile_command, MAX_PATH_LENGTH, COMPILE_COMMAND, kata.path.str);

    // Compile kata file
    if (system(compile_command) != 0) {
        strncpy(result_buffer.str, "Compilation error", result_buffer.len);
        return KATA_COMPILATION_FAILURE;
    }

    // Run compiled kata file
    FILE *fp = popen(RUN_COMMAND, "r");
    if (fp == NULL) {
        strncpy(result_buffer.str, "Execution error", result_buffer.len);
        return KATA_EXECUTION_FAILURE;
    }

    // Read output to result_buffer
    fread(result_buffer.str, result_buffer.len, 1, fp);
    int status = pclose(fp);

    // Check execution status
    if (status != 0) {
        strncpy(result_buffer.str, "Execution error", result_buffer.len);
        return KATA_EXECUTION_FAILURE;
    }

    return KATA_SUCCESS;
}
