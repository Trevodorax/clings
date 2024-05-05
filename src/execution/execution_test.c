

#include "stdlib.h"
#include "stdio.h"
#include "test_utils.h"
#include "execution.h"

static test_result all_tests(void);


int main(void) {
    const char *result = all_tests();
    if (result == NULL) {
        printf("ALL TESTS PASSED\n");
    } else {
        printf("%s\n", result);
    }

    return EXIT_SUCCESS;
}

kata_t kata;
popen_f mock_fopen; // set to memory_fopen before each test
popen_f mock_popen; // set to memory_popen before each test
pclose_f mock_pclose; // set to success_pclose before each test
infrastructure_t infrastructure;
run_kata_result_t kata_result_compile_success;
run_kata_result_t kata_result_compile_failed;
run_kata_result_t kata_result_run_success;
run_kata_result_t kata_result_run_failed;

void before_each(void) {
    kata = (kata_t) {
            .name = new_sized_string_from("name"),
            .path = new_sized_string_from("path"),
            .is_done = false
    };

    mock_fopen = memory_fopen();
    mock_popen = memory_popen();
    mock_pclose = success_pclose();
    infrastructure = (infrastructure_t) {.fopen = mock_fopen, .popen = mock_popen, .pclose = mock_pclose,};
    kata_result_compile_success = run_kata_result(kata, KATA_COMPILATION_SUCCESS,
                                                  new_sized_string_from("compiled successfully.\n"));
    kata_result_compile_failed = run_kata_result(kata, KATA_COMPILATION_FAILURE,
                                                 new_sized_string_from("failed to compile.\n"));
    kata_result_run_success = run_kata_result(kata, KATA_SUCCESS,
                                              new_sized_string_from("content printed in the kata...\n"));
    kata_result_run_failed = run_kata_result(kata, KATA_COMPILATION_FAILURE,
                                             new_sized_string_from("failed to run. error : ...\n"));
}


void tear_down(void) {
    free_kata(&kata);
}

static test_result should_successfully_run_kata_when_compilation_and_run_succeeded(void);

static test_result should_get_compilation_error_when_compilation_failed(void);

static test_result should_get_file_not_found_if_file_does_not_exists(void);

static test_result compile_should_success_if_all_succeed(void);

static test_result compile_should_get_compilation_error_if_call_to_compile_process_failed(void);

static test_result compile_should_get_compilation_error_if_compilation_exits_with_failure_code(void);

static test_result run_should_success_if_all_succeed(void);

static test_result should_not_run_if_compilation_failed(void);

static test_result run_should_get_execution_error_if_call_to_run_process_failed(void);

static test_result run_should_get_execution_error_if_run_exits_with_failure_code(void);

static test_result all_tests(void) {
    run_test(should_successfully_run_kata_when_compilation_and_run_succeeded);
    run_test(should_get_compilation_error_when_compilation_failed);
    run_test(should_get_file_not_found_if_file_does_not_exists);
    run_test(compile_should_success_if_all_succeed);
    run_test(compile_should_get_compilation_error_if_call_to_compile_process_failed);
    run_test(compile_should_get_compilation_error_if_compilation_exits_with_failure_code);
    run_test(run_should_success_if_all_succeed);
    run_test(should_not_run_if_compilation_failed);
    run_test(run_should_get_execution_error_if_call_to_run_process_failed);
    run_test(run_should_get_execution_error_if_run_exits_with_failure_code);

    return EXIT_SUCCESS;
}

run_kata_result_t compile_success(__attribute__((unused)) kata_t k, __attribute__((unused)) popen_f popen,
                                  __attribute__((unused)) pclose_f pclose) {
    return kata_result_compile_success;
}

run_kata_result_t compile_fails(__attribute__((unused)) kata_t k, __attribute__((unused)) popen_f popen,
                                __attribute__((unused)) pclose_f pclose) {
    return kata_result_compile_failed;
}

run_kata_result_t run_success(__attribute__((unused)) run_kata_result_t compiled, __attribute__((unused)) popen_f popen,
                              __attribute__((unused)) pclose_f pclose) {
    return kata_result_run_success;
}

run_kata_result_t run_failed(__attribute__((unused)) run_kata_result_t compiled, __attribute__((unused)) popen_f popen,
                             __attribute__((unused)) pclose_f pclose) {
    return kata_result_run_failed;
}


static test_result should_successfully_run_kata_when_compilation_and_run_succeeded(void) {
    run_kata_result_t result = run_kata_with_compiler_and_runner(kata, &compile_success, &run_success, infrastructure);
    assert_value_strict_equals_expected(result.status, KATA_SUCCESS);
    assert_string_equals_expected(result.output.str, "compiled successfully.\ncontent printed in the kata...\n");

    free_sized_string(&result.output);
    free_sized_string(&kata_result_compile_failed.error);
    free_sized_string(&kata_result_run_failed.error);
    return TEST_SUCCESS;
}

static test_result should_get_compilation_error_when_compilation_failed(void) {
    run_kata_result_t result = run_kata_with_compiler_and_runner(kata, &compile_fails, &run_failed, infrastructure);
    assert_value_strict_equals_expected(result.status, KATA_COMPILATION_FAILURE);
    assert_string_equals_expected(result.output.str, "failed to run. error : ...\n");

    free_sized_string(&result.error);
    free_sized_string(&kata_result_compile_success.output);
    free_sized_string(&kata_result_run_success.output);
    return TEST_SUCCESS;
}

static test_result should_get_file_not_found_if_file_does_not_exists(void) {
    infrastructure.fopen = failing_fopen();
    run_kata_result_t result = run_kata_with_compiler_and_runner(kata, &compile_success, &run_success, infrastructure);
    assert_value_strict_equals_expected(result.status, KATA_ERROR);
    assert_string_equals_expected(result.error.str, "Kata in file [path] not found.");

    free_sized_string(&result.error);
    free_sized_string(&kata_result_compile_success.output);
    free_sized_string(&kata_result_run_success.output);
    free_sized_string(&kata_result_compile_failed.error);
    free_sized_string(&kata_result_run_failed.error);
    return TEST_SUCCESS;
}

static test_result compile_should_success_if_all_succeed(void) {
    run_kata_result_t result = compile_with_popen_and_pclose(kata, mock_popen, mock_pclose);
    assert_value_strict_equals_expected(result.status, KATA_COMPILATION_SUCCESS);
    assert_string_equals_expected(result.output.str, "buffer");

    free_sized_string(&result.output);
    free_sized_string(&kata_result_compile_success.output);
    free_sized_string(&kata_result_run_success.output);
    free_sized_string(&kata_result_compile_failed.error);
    free_sized_string(&kata_result_run_failed.error);
    return TEST_SUCCESS;
}

static test_result compile_should_get_compilation_error_if_call_to_compile_process_failed(void) {
    run_kata_result_t result = compile_with_popen_and_pclose(kata, failing_popen(), mock_pclose);
    assert_value_strict_equals_expected(result.status, KATA_COMPILATION_FAILURE);
    assert_string_equals_expected(result.error.str, "Execution of command [gcc -o /tmp/kata path 2>&1] failed.");

    free_sized_string(&result.error);
    free_sized_string(&kata_result_compile_success.output);
    free_sized_string(&kata_result_run_success.output);
    free_sized_string(&kata_result_compile_failed.error);
    free_sized_string(&kata_result_run_failed.error);
    return TEST_SUCCESS;
}

static test_result compile_should_get_compilation_error_if_compilation_exits_with_failure_code(void) {
    run_kata_result_t result = compile_with_popen_and_pclose(kata, mock_popen, failing_pclose());
    assert_value_strict_equals_expected(result.status, KATA_COMPILATION_FAILURE);
    assert_string_equals_expected(result.error.str, "Compilation of kata [path] failed : \nbuffer");

    free_sized_string(&result.error);
    free_sized_string(&kata_result_compile_success.output);
    free_sized_string(&kata_result_run_success.output);
    free_sized_string(&kata_result_compile_failed.error);
    free_sized_string(&kata_result_run_failed.error);
    return TEST_SUCCESS;
}

static test_result run_should_success_if_all_succeed(void) {
    run_kata_result_t result = run_with_popen_and_pclose(kata_result_compile_success, mock_popen, mock_pclose);
    assert_value_strict_equals_expected(result.status, KATA_SUCCESS);
    assert_string_equals_expected(result.output.str, "buffer");

    free_sized_string(&result.output);
    free_sized_string(&kata_result_compile_success.output);
    free_sized_string(&kata_result_run_success.output);
    free_sized_string(&kata_result_compile_failed.error);
    free_sized_string(&kata_result_run_failed.error);
    return TEST_SUCCESS;
}

static test_result should_not_run_if_compilation_failed(void) {
    run_kata_result_t result = run_with_popen_and_pclose(kata_result_compile_failed, mock_popen, mock_pclose);
    assert_value_strict_equals_expected(result.status, KATA_COMPILATION_FAILURE);
    assert_string_equals_expected(result.output.str, "failed to compile.\n");

    free_sized_string(&result.error);
    free_sized_string(&kata_result_compile_success.output);
    free_sized_string(&kata_result_run_success.output);
    free_sized_string(&kata_result_run_failed.error);
    return TEST_SUCCESS;
}

static test_result run_should_get_execution_error_if_call_to_run_process_failed(void) {
    run_kata_result_t result = run_with_popen_and_pclose(kata_result_compile_success, failing_popen(), mock_pclose);
    assert_value_strict_equals_expected(result.status, KATA_EXECUTION_FAILURE);
    assert_string_equals_expected(result.error.str, "Execution of command [/tmp/kata] failed.");

    free_sized_string(&result.error);
    free_sized_string(&kata_result_compile_success.output);
    free_sized_string(&kata_result_run_success.output);
    free_sized_string(&kata_result_compile_failed.error);
    free_sized_string(&kata_result_run_failed.error);
    return TEST_SUCCESS;
}

static test_result run_should_get_execution_error_if_run_exits_with_failure_code(void) {
    run_kata_result_t result = run_with_popen_and_pclose(kata_result_compile_success, mock_popen, failing_pclose());
    assert_value_strict_equals_expected(result.status, KATA_EXECUTION_FAILURE);
    assert_string_equals_expected(result.error.str, "Execution of kata [path] failed : \nbuffer");

    free_sized_string(&result.error);
    free_sized_string(&kata_result_compile_success.output);
    free_sized_string(&kata_result_run_success.output);
    free_sized_string(&kata_result_compile_failed.error);
    free_sized_string(&kata_result_run_failed.error);
    return TEST_SUCCESS;
}

