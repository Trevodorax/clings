#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "execution.h"


run_kata_result_t run_kata_result_of(kata_t kata, const char * message_to_fill, kata_status status);
run_kata_result_t kata_not_found(kata_t kata);
run_kata_result_t compilation_failed(kata_t kata, sized_string_t output_error);
run_kata_result_t execution_failed(kata_t kata);
run_kata_result_t execution_success(sized_string_t output);
sized_string_t get_compile_command_for_kata(kata_t kata);


run_kata_result_t compile(kata_t kata);

run_kata_result_t run(const kata_t kata);

run_kata_result_t run_kata(const kata_t kata) {

    if(!kata_file_exists(kata)) {
        return kata_not_found(kata);
    }

    run_kata_result_t compilation = compile(kata);
    if(compilation.status != KATA_COMPILATION_SUCCESS) {
        return compilation;
    }


    run_kata_result_t execution = run(kata);
    if(execution.status != KATA_SUCCESS) {
        return execution;
    }

    // get full output
    sized_string_t full_output = concat_two_sized_string(compilation.output, execution.output);
    free_sized_string(&compilation.output);
    free_sized_string(&execution.output);
    return execution_success(full_output);
}

run_kata_result_t run(const kata_t kata) {
    // TODO maybe take the compilation in param
    FILE *kata_process = popen(RUN_COMMAND, "r");
    if (kata_process == NULL) {
        return execution_failed(kata);
    }

    sized_string_t run_output = new_sized_string_of_length(MAX_OUTPUT_SIZE);
    fread(run_output.str, run_output.len, 1, kata_process);
    run_output.len = strlen(run_output.str);

    // Check execution status
    if (pclose(kata_process) != EXIT_SUCCESS) {
        return execution_failed(kata); // TODO pass the output in error message
    }

    return (run_kata_result_t) {
        .status = KATA_SUCCESS,
        .output = run_output
    };
}

run_kata_result_t compile(const kata_t kata) {
    sized_string_t compile_command = get_compile_command_for_kata(kata);

    FILE* compilation_process = popen(compile_command.str, "r");
    if (compilation_process == NULL) {
        return compilation_failed(kata, new_sized_string_from("call to compile command failed."));
    }
    free_sized_string(&compile_command);

    sized_string_t compilation_output = new_sized_string_of_length(MAX_OUTPUT_SIZE);
    fread(compilation_output.str, compilation_output.len, 1, compilation_process);
    compilation_output.len = strlen(compilation_output.str);
    if(pclose(compilation_process) != EXIT_SUCCESS) {
        return compilation_failed(kata, compilation_output);
    }

    return (run_kata_result_t ) {
        .status = KATA_COMPILATION_SUCCESS,
        .output = compilation_output,
    };
}

sized_string_t get_compile_command_for_kata(kata_t kata) {
    sized_string_t command = new_sized_string_of_length(MAX_PATH_LENGTH);
    snprintf(command.str, MAX_PATH_LENGTH, COMPILE_COMMAND, kata.path.str);
    return command;
}

run_kata_result_t run_kata_result(kata_status status, sized_string_t error_message)  {
    run_kata_result_t result = {
            .status = status,
            .error = error_message,
    };
    return result;
}

run_kata_result_t run_kata_result_of(kata_t kata, const char * message_to_fill, kata_status status) {
    size_t full_message_length = strlen(message_to_fill) + kata.path.len;
    if(full_message_length > MAX_OUTPUT_SIZE) {
        full_message_length = MAX_OUTPUT_SIZE;
    }
    sized_string_t error_message = new_sized_string_of_length(full_message_length);
    snprintf(error_message.str, full_message_length, message_to_fill, kata.path);
    return run_kata_result(status, error_message);
}

run_kata_result_t kata_not_found(kata_t kata) {
    return run_kata_result_of(kata, "Kata in file [%s] not found.", KATA_ERROR);
}

run_kata_result_t compilation_failed(kata_t kata, sized_string_t output_error) {
    const char * message = "Compilation of kata [%s] failed : \n%s";
    size_t full_message_length = strlen(message) + kata.path.len + output_error.len;
    if(full_message_length > MAX_OUTPUT_SIZE) {
        full_message_length = MAX_OUTPUT_SIZE;
    }
    sized_string_t error_message = new_sized_string_of_length(full_message_length);
    snprintf(error_message.str, full_message_length, message, kata.path.str, output_error.str);
    return run_kata_result(KATA_COMPILATION_FAILURE, error_message);
}

run_kata_result_t execution_failed(kata_t kata) {
    return run_kata_result_of(kata, "Execution of kata [%s] failed.", KATA_EXECUTION_FAILURE);
}

run_kata_result_t execution_success(sized_string_t output) {
    run_kata_result_t result = {
            .status = KATA_SUCCESS,
            .output = output,
    };
    return result;
}
