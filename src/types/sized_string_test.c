#include "types.h"
#include "string.h"
#include "stdio.h"
#include "test_utils.h"


static const char * all_tests(void);

int main(void) {
    const char * result = all_tests();
    if(result == NULL) {
        printf("ALL TESTS PASSED\n");
    } else {
        printf("%s\n", result);
    }

    return EXIT_SUCCESS;
}


sized_string_t string = {.str = NULL, .len = 0};
void before_each(void) {}

void tear_down(void) {
    free_sized_string(&string);
}

static test_result should_create_new_sized_string_of_length(void);
static test_result should_create_new_sized_string_of_length_zero(void);
static test_result should_get_null_string_if_memory_allocation_fails(void);
static test_result should_create_new_sized_string_from_existing_string(void);
static test_result should_create_new_sized_string_from_empty_string(void);
static test_result should_create_new_sized_string_from_NULL(void);
static test_result should_clone_string(void);
static test_result cloned_sized_string_should_have_different_memory_address(void);
static test_result clone_NULL_should_create_empty_string(void);
static test_result should_concat_two_strings(void);
static test_result should_concat_with_empty_string(void);
static test_result should_concat_with_null_string(void);
static test_result free_sized_string_should_set_pointer_to_NULL_and_length_to_zero(void);
static test_result free_NULL_sized_string_should_do_nothing(void);
static test_result should_create_new_sized_string_from_str_with_length(void);
static test_result create_new_sized_string_from_str_with_more_length_than_enough_should_fill_with_terminating_char(void);
static test_result create_new_sized_string_from_str_with_not_enough_should_truncate_string(void);
static test_result create_new_sized_string_from_NULL_should_create_empty_string(void);

static test_result all_tests(void) {
    run_test(should_create_new_sized_string_of_length);
    run_test(should_create_new_sized_string_of_length_zero);
    run_test(should_get_null_string_if_memory_allocation_fails);
    run_test(should_create_new_sized_string_from_existing_string);
    run_test(should_create_new_sized_string_from_empty_string);
    run_test(should_create_new_sized_string_from_NULL);
    run_test(should_clone_string);
    run_test(cloned_sized_string_should_have_different_memory_address);
    run_test(clone_NULL_should_create_empty_string);
    run_test(should_concat_two_strings);
    run_test(should_concat_with_empty_string);
    run_test(should_concat_with_null_string);
    run_test(free_sized_string_should_set_pointer_to_NULL_and_length_to_zero);
    run_test(free_NULL_sized_string_should_do_nothing);
    run_test(should_create_new_sized_string_from_str_with_length);
    run_test(create_new_sized_string_from_str_with_more_length_than_enough_should_fill_with_terminating_char);
    run_test(create_new_sized_string_from_str_with_not_enough_should_truncate_string);
    run_test(create_new_sized_string_from_NULL_should_create_empty_string);
    return NULL;
}


static test_result should_create_new_sized_string_of_length(void) {
    string = new_sized_string_of_length(5);
    assert_is_not_null(string.str);
    assert_value_strict_equals_expected(string.len, 5);
    for(int i = 0; i < 5; i++) {
        assert_value_strict_equals_expected(string.str[i], '\0');
    }

    // null terminating char at the end
    assert_value_strict_equals_expected(string.str[5], '\0');

    return TEST_SUCCESS;
}

static test_result should_create_new_sized_string_of_length_zero(void) {
    string = new_sized_string_of_length(0);
    assert_is_not_null(string.str);
    assert_value_strict_equals_expected(string.len, 0);
    assert_value_strict_equals_expected(string.str[0], '\0');

    return TEST_SUCCESS;
}

void * failing_calloc(__attribute__((unused)) size_t count, __attribute__((unused)) size_t size) {
    return NULL;
}

static test_result should_get_null_string_if_memory_allocation_fails(void) {
    string = new_sized_string_of_length_with_calloc(5, &failing_calloc);

    assert_is_null(string.str);
    assert_value_strict_equals_expected(string.len, 0);

    return TEST_SUCCESS;
}

static test_result should_create_new_sized_string_from_existing_string(void) {
    string = new_sized_string_from("clings");
    assert_is_not_null(string.str);
    assert_value_strict_equals_expected(string.len, 6);
    assert_string_equals_expected(string.str, "clings");

    return TEST_SUCCESS;
}

// test length limit ? (currently no limit)

static test_result should_create_new_sized_string_from_empty_string(void) {
    string = new_sized_string_from("");
    assert_is_not_null(string.str);
    assert_value_strict_equals_expected(string.len, 0);
    assert_string_equals_expected(string.str, "");
    assert_value_strict_equals_expected(string.str[0], '\0');

    return TEST_SUCCESS;
}


static test_result should_create_new_sized_string_from_NULL(void) {
    string = new_sized_string_from(NULL);
    assert_is_not_null(string.str);
    assert_value_strict_equals_expected(string.len, 0);
    assert_string_equals_expected(string.str, "");
    assert_value_strict_equals_expected(string.str[0], '\0');

    return TEST_SUCCESS;
}

static test_result should_clone_string(void) {
    sized_string_t original = new_sized_string_from("clings");
    sized_string_t clone = clone_sized_string(original);

    assert_is_not_null(clone.str);
    assert_value_strict_equals_expected(clone.len, 6);
    assert_string_equals_expected(clone.str, "clings");
    assert_value_strict_equals_expected(clone.str[6], '\0');

    free_sized_string(&original);
    free_sized_string(&clone);

    return TEST_SUCCESS;
}

static test_result cloned_sized_string_should_have_different_memory_address(void) {
    sized_string_t original = new_sized_string_from("clings");
    sized_string_t clone = clone_sized_string(original);

    assert_values_are_different(&(original.str), &(clone.str));

    free_sized_string(&original);
    free_sized_string(&clone);

    return TEST_SUCCESS;
}

static test_result clone_NULL_should_create_empty_string(void) {
    sized_string_t original = new_sized_string_from(NULL);
    sized_string_t clone = clone_sized_string(original);

    assert_is_not_null(clone.str);
    assert_value_strict_equals_expected(clone.len, 0);
    assert_string_equals_expected(clone.str, "");

    free_sized_string(&original);
    free_sized_string(&clone);

    return TEST_SUCCESS;
}


static test_result should_concat_two_strings(void) {
    sized_string_t first = new_sized_string_from("Hello ");
    sized_string_t second = new_sized_string_from("world!");
    sized_string_t concat = concat_two_sized_string(first, second);

    assert_is_not_null(concat.str);
    assert_value_strict_equals_expected(concat.len, 12);
    assert_string_equals_expected(concat.str, "Hello world!");

    free_sized_string(&first);
    free_sized_string(&second);
    free_sized_string(&concat);

    return TEST_SUCCESS;
}

static test_result should_concat_with_empty_string(void) {
    sized_string_t first = new_sized_string_from("Hello ");
    sized_string_t second = new_sized_string_from("");
    sized_string_t concat = concat_two_sized_string(first, second);

    assert_is_not_null(concat.str);
    assert_value_strict_equals_expected(concat.len, 6);
    assert_string_equals_expected(concat.str, "Hello ");

    free_sized_string(&first);
    free_sized_string(&second);
    free_sized_string(&concat);

    first = new_sized_string_from("");
    second = new_sized_string_from("world !");
    concat = concat_two_sized_string(first, second);

    assert_is_not_null(concat.str);
    assert_value_strict_equals_expected(concat.len, 7);
    assert_string_equals_expected(concat.str, "world !");

    free_sized_string(&first);
    free_sized_string(&second);
    free_sized_string(&concat);

    return TEST_SUCCESS;
}

static test_result should_concat_with_null_string(void) {
    sized_string_t first = new_sized_string_from("Hello ");
    sized_string_t second = (sized_string_t) {.str = NULL, .len = 2};
    sized_string_t concat = concat_two_sized_string(first, second);

    assert_is_not_null(concat.str);
    assert_value_strict_equals_expected(concat.len, 6);
    assert_string_equals_expected(concat.str, "Hello ");

    free_sized_string(&first);
    free_sized_string(&second);
    free_sized_string(&concat);


    first = (sized_string_t) {.str = NULL, .len = 3};
    second = new_sized_string_from("world !");
    concat = concat_two_sized_string(first, second);

    assert_is_not_null(concat.str);
    assert_value_strict_equals_expected(concat.len, 7);
    assert_string_equals_expected(concat.str, "world !");

    free_sized_string(&first);
    free_sized_string(&second);
    free_sized_string(&concat);

    return TEST_SUCCESS;
}

static test_result free_sized_string_should_set_pointer_to_NULL_and_length_to_zero(void) {
    string = new_sized_string_from("clings");
    free_sized_string(&string);
    assert_is_null(string.str);
    assert_value_strict_equals_expected(string.len, 0);

    return TEST_SUCCESS;
}

static test_result free_NULL_sized_string_should_do_nothing(void) {
    string = (sized_string_t) {.str = NULL, .len = 0};
    free_sized_string(&string);
    assert_is_null(string.str);

    return TEST_SUCCESS;
}


static test_result should_create_new_sized_string_from_str_with_length(void) {
    string = new_sized_string_from_str_of_length("clings", 6);

    assert_is_not_null(string.str);
    assert_value_strict_equals_expected(string.len, 6);
    assert_string_equals_expected(string.str, "clings");

    return TEST_SUCCESS;
}

static test_result create_new_sized_string_from_str_with_more_length_than_enough_should_fill_with_terminating_char(void) {
    string = new_sized_string_from_str_of_length("abc", 6);

    assert_is_not_null(string.str);
    assert_value_strict_equals_expected(string.len, 6);
    assert_string_equals_expected(string.str, "abc");
    for(int i = 3; i < 7; i++) {
        assert_value_strict_equals_expected(string.str[i], '\0');
    }

    return TEST_SUCCESS;
}

static test_result create_new_sized_string_from_str_with_not_enough_should_truncate_string(void) {
    string = new_sized_string_from_str_of_length("abcdef", 3);

    assert_is_not_null(string.str);
    assert_value_strict_equals_expected(string.len, 3);
    assert_string_equals_expected(string.str, "abc");

    return TEST_SUCCESS;
}

static test_result create_new_sized_string_from_NULL_should_create_empty_string(void) {
    string = new_sized_string_from_str_of_length(NULL, 3);

    assert_is_not_null(string.str);
    assert_value_strict_equals_expected(string.len, 0);
    assert_string_equals_expected(string.str, "");

    return TEST_SUCCESS;
}
