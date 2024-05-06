#include "stdlib.h"
#include "stdio.h"
#include "test_utils.h"
#include "katas/katas.h"

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

kata_list_t list = {.katas = NULL, .len = 0};
#define new_kata (kata_t){.name = new_sized_string_from("new kata"), .path = new_sized_string_from("new"), .is_done = false }

void before_each(void) {
    list.len = 3;
    list.katas = malloc(sizeof(kata_t) * list.len);
    list.katas[0] = (kata_t) {.name = new_sized_string_from("first"), .path = new_sized_string_from("f"), .is_done = true };
    list.katas[1] = (kata_t) {.name = new_sized_string_from("second"), .path = new_sized_string_from("s"), .is_done = false };
    list.katas[2] = (kata_t) {.name = new_sized_string_from("third"), .path = new_sized_string_from("t"), .is_done = false };
}

void tear_down(void) {
    free_kata_list(&list);
}

static test_result should_push_in_kata_list(void);
static test_result push_in_null_kata_list_should_create_list_of_one_kata(void);
static test_result push_in_null_kata_list_should_do_nothing_if_allocation_failed(void);
static test_result free_kata_list_should_set_list_to_null_and_length_to_zero(void);
static test_result free_kata_should_set_name_and_path_to_null(void);
static test_result should_not_find_kata_file_when_fopen_returns_null(void);
static test_result should_find_kata_file_when_fopen_finds_file(void);
static test_result should_not_find_kata_file_when_path_is_null(void);


static test_result all_tests(void) {
    run_test(should_push_in_kata_list);
    run_test(push_in_null_kata_list_should_create_list_of_one_kata);
    run_test(push_in_null_kata_list_should_do_nothing_if_allocation_failed);
    run_test(free_kata_list_should_set_list_to_null_and_length_to_zero);
    run_test(free_kata_should_set_name_and_path_to_null);
    run_test(should_not_find_kata_file_when_fopen_returns_null);
    run_test(should_find_kata_file_when_fopen_finds_file);
    run_test(should_not_find_kata_file_when_path_is_null);

    return EXIT_SUCCESS;
}

static test_result should_push_in_kata_list(void) {
    push_kata_in_list(new_kata, &list);

    assert_value_strict_equals_expected(list.len, 4);
    assert_string_equals_expected("new kata", list.katas[3].name.str);
    assert_string_equals_expected("new", list.katas[3].path.str);
    assert_value_strict_equals_expected(list.katas[3].is_done, false);

    return TEST_SUCCESS;
}

static test_result push_in_null_kata_list_should_create_list_of_one_kata(void) {
    kata_list_t null_list = {.katas = NULL, .len = 3};

    push_kata_in_list(new_kata, &null_list);

    assert_value_strict_equals_expected(null_list.len, 1);
    assert_string_equals_expected("new kata", null_list.katas[0].name.str);
    assert_string_equals_expected("new", null_list.katas[0].path.str);
    assert_value_strict_equals_expected(null_list.katas[0].is_done, false);

    return TEST_SUCCESS;
}


static test_result push_in_null_kata_list_should_do_nothing_if_allocation_failed(void) {
    push_kata_in_list_with_realloc(new_kata, &list, failing_realloc());

    assert_value_strict_equals_expected(list.len, 3);

    return TEST_SUCCESS;
}



static test_result free_kata_list_should_set_list_to_null_and_length_to_zero(void) {
    free_kata_list(&list);

    assert_is_null(list.katas);
    assert_value_strict_equals_expected(list.len, 0);

    return TEST_SUCCESS;
}

static test_result free_kata_should_set_name_and_path_to_null(void) {
    free_kata(&list.katas[0]);

    assert_is_null(list.katas[0].name.str);
    assert_is_null(list.katas[0].path.str);

    return TEST_SUCCESS;
}


static test_result should_not_find_kata_file_when_fopen_returns_null(void) {
    assert_false(kata_file_exists(list.katas[0], failing_fopen()));

    return TEST_SUCCESS;
}

static test_result should_find_kata_file_when_fopen_finds_file(void) {
    assert_true(kata_file_exists(list.katas[0], memory_fopen()));

    return TEST_SUCCESS;
}

static test_result should_not_find_kata_file_when_path_is_null(void) {
    sized_string_t null_str = (sized_string_t) {.str = NULL, .len = 0};
    kata_t kata = {.name = null_str, .path = null_str};
    assert_false(kata_file_exists(kata, memory_fopen()));

    return TEST_SUCCESS;
}
