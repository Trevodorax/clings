#include <string.h>
#include "execution.h"
#include "execution_errors.h"


run_kata_result_t execution_success(kata_t kata, sized_string_t output);

sized_string_t get_compile_command_for_kata(kata_t kata);

run_kata_result_t compile(kata_t kata, popen_f popen, pclose_f pclose);

run_kata_result_t run(run_kata_result_t compilation, popen_f popen, pclose_f pclose);


run_kata_result_t run_kata_with_fopen_and_popen(const kata_t kata, fopen_f fopen, popen_f popen, pclose_f pclose) {

    if (!kata_file_exists(kata, fopen)) {
        return kata_not_found(kata);
    }

    run_kata_result_t compiled = compile(kata, popen, pclose);
    run_kata_result_t execution = run(compiled, popen, pclose);
    if (execution.status != KATA_SUCCESS) {
        return execution;
    }

    sized_string_t full_output = concat_two_sized_string(compiled.output, execution.output);
    free_sized_string(&compiled.output);
    free_sized_string(&execution.output);

    return execution_success(kata, full_output);
}

run_kata_result_t compile(const kata_t kata, popen_f popen, pclose_f pclose) {
    sized_string_t compile_command = get_compile_command_for_kata(kata);

    FILE *compilation_process = (*popen)(compile_command.str, "r");
    if (compilation_process == NULL) {
        return open_process_failed(kata, compile_command, KATA_COMPILATION_FAILURE);
    }
    free_sized_string(&compile_command);

    sized_string_t compilation_output = new_sized_string_of_length(MAX_OUTPUT_SIZE);
    fread(compilation_output.str, compilation_output.len, 1, compilation_process);
    compilation_output.len = strlen(compilation_output.str);
    if ((*pclose)(compilation_process) != EXIT_SUCCESS) {
        return compilation_failed(kata, compilation_output);
    }

    return (run_kata_result_t) {
            .kata = kata,
            .status = KATA_COMPILATION_SUCCESS,
            .output = compilation_output,
    };
}

run_kata_result_t run(const run_kata_result_t compilation, popen_f popen, pclose_f pclose) {
    if (compilation.status != KATA_COMPILATION_SUCCESS) {
        return compilation;
    }

    FILE *execution_process = (*popen)(RUN_COMMAND, "r");
    if (execution_process == NULL) {
        return open_process_failed(compilation.kata, new_sized_string_from(RUN_COMMAND), KATA_EXECUTION_FAILURE);
    }

    sized_string_t run_output = new_sized_string_of_length(MAX_OUTPUT_SIZE);
    fread(run_output.str, run_output.len, 1, execution_process);
    run_output.len = strlen(run_output.str);

    if (pclose(execution_process) != EXIT_SUCCESS) {
        return execution_failed(compilation.kata, run_output);
    }

    return (run_kata_result_t) {
            .status = KATA_SUCCESS,
            .output = run_output
    };
}

sized_string_t get_compile_command_for_kata(kata_t kata) {
    sized_string_t command = new_sized_string_of_length(MAX_PATH_LENGTH);
    snprintf(command.str, MAX_PATH_LENGTH, COMPILE_COMMAND, RUN_COMMAND, kata.path.str);
    return command;
}


run_kata_result_t execution_success(kata_t kata, sized_string_t output) {
    return run_kata_result(kata, KATA_SUCCESS, output);
}
