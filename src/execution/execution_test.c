

#include "stdlib.h"
#include "stdio.h"
#include "test_utils.h"
#include "execution.h"

#define BUFFER_SIZE 512

static test_result all_tests(void);


int main(void) {
    const char * result = all_tests();
    if(result == NULL) {
        printf("ALL TESTS PASSED\n");
    } else {
        printf("%s\n", result);
    }

    return EXIT_SUCCESS;
}

kata_t kata;
sized_string_t buffer = {.str = NULL, .len = 0};
popen_f current_popen = &popen; // set to memory_popen before each test
pclose_f current_pclose = &pclose; // set to success_pclose before each test

void before_each(void) {
    kata = (kata_t) {
        .name = new_sized_string_from("name"),
        .path = new_sized_string_from("path"),
        .is_done = false
    };
    buffer = new_sized_string_of_length(BUFFER_SIZE);
    current_popen = memory_popen();
    current_pclose = success_pclose();
}

void tear_down(void) {
    free_kata(&kata);
    free_sized_string(&buffer);
}

static test_result should_get_file_not_found_if_file_does_not_exists(void);
static test_result should_get_open_process_failed_if_compilator_popen_fails_to_call_compilation_command(void);
static test_result should_get_compilation_error_if_compilator_pclose_get_failed_exit_code(void);
static test_result should_get_execution_error_if_runner_popen_failed(void);
static test_result should_get_execution_error_if_runner_pclose_get_failure_exit_code(void);

static test_result all_tests(void) {
    run_test(should_get_file_not_found_if_file_does_not_exists);
    run_test(should_get_open_process_failed_if_compilator_popen_fails_to_call_compilation_command);
    run_test(should_get_compilation_error_if_compilator_pclose_get_failed_exit_code);
    run_test(should_get_execution_error_if_runner_popen_failed);
    run_test(should_get_execution_error_if_runner_pclose_get_failure_exit_code);

    return EXIT_SUCCESS;
}

static test_result should_get_file_not_found_if_file_does_not_exists(void) {
    run_kata_result_t result = run_kata_with_fopen_and_popen(kata, failing_fopen(), &popen, &pclose);
    assert_value_strict_equals_expected(result.status, KATA_ERROR);
    assert_string_equals_expected(result.error.str, "Kata in file [path] not found.");
    return TEST_SUCCESS;
}

static test_result should_get_open_process_failed_if_compilator_popen_fails_to_call_compilation_command(void) {
    run_kata_result_t result = run_kata_with_fopen_and_popen(kata, memory_fopen(), failing_popen(), &pclose);
    assert_value_strict_equals_expected(result.status, KATA_COMPILATION_FAILURE);
    assert_string_equals_expected(result.error.str, "Execution of command [gcc -o /tmp/kata path 2>&1] failed.");
    return TEST_SUCCESS;
}

static test_result should_get_compilation_error_if_compilator_pclose_get_failed_exit_code(void) {
    run_kata_result_t result = run_kata_with_fopen_and_popen(kata, memory_fopen(), memory_popen(), failing_pclose());
    assert_value_strict_equals_expected(result.status, KATA_COMPILATION_FAILURE);
    assert_string_equals_expected(result.error.str, "Compilation of kata [path] failed : \nbuffer");
    return TEST_SUCCESS;
}

FILE * memory_then_failing_popen_f(const char * command, const char * mode) {
    if(current_popen == memory_popen()) {
        current_popen = failing_popen();
        return memory_popen()(command, mode);
    } else {
        return failing_popen()(command, mode);
    }
}


static test_result should_get_execution_error_if_runner_popen_failed(void) {
    run_kata_result_t result = run_kata_with_fopen_and_popen(kata, memory_fopen(), &memory_then_failing_popen_f, success_pclose());
    assert_value_strict_equals_expected(result.status, KATA_EXECUTION_FAILURE);
    assert_string_equals_expected(result.error.str, "Execution of command [/tmp/kata] failed.");
    return TEST_SUCCESS;
}


int success_then_failing_pclose(FILE * stream) {
    if(current_pclose == success_pclose()) {
        current_pclose = failing_pclose();
        return success_pclose()(stream);
    } else {
        return failing_pclose()(stream);
    }
}

static test_result should_get_execution_error_if_runner_pclose_get_failure_exit_code(void) {
    run_kata_result_t result = run_kata_with_fopen_and_popen(kata, memory_fopen(), memory_popen(), &success_then_failing_pclose);
    assert_value_strict_equals_expected(result.status, KATA_EXECUTION_FAILURE);
    assert_string_equals_expected(result.error.str, "Execution of kata [path] failed : \nbuffer");
    return TEST_SUCCESS;
}

