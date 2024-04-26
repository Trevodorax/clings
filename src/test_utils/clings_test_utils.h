#ifndef CLINGS_CLINGS_TEST_UTILS_H
#define CLINGS_CLINGS_TEST_UTILS_H

#include "stdlib.h"


#define stringify(x) #x
#define error_output_string(file, line, message) file ":" stringify(line) ": error: " message

#define run_test(test) before_each(); { const char * msg = test(); if (msg) return msg; } tear_down()
#define cling_assert(test, message) if (!(test)) return error_output_string(__FILE__, __LINE__, message)
#define assert_string_equals_expected(str, expected) cling_assert(strcmp(str, expected) == 0, #str " should be equals to [" #expected "].")
#define assert_value_strict_equals_expected(value, expected) cling_assert(value == expected, #value " should be strictly equals to [" #expected "].")
#define assert_values_are_different(value1, value2) cling_assert(value1 != value2, #value1 " should NOT be equals to [" #value2 "].")
#define assert_is_null(value) cling_assert(value == NULL, #value " should be NULL.")
#define assert_is_not_null(value) cling_assert(value != NULL, #value " should NOT be NULL.")

#define TEST_SUCCESS EXIT_SUCCESS
typedef const char * test_result;

#endif //CLINGS_CLINGS_TEST_UTILS_H
