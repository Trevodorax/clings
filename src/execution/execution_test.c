
// TODO refacto run_kata to take the I/O tools in param

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

sized_string_t buffer = {.str = NULL, .len = 0};

void before_each(void) {
    buffer = new_sized_string_of_length(BUFFER_SIZE);
}

void tear_down(void) {
    free_sized_string(&buffer);
}

static test_result should_get_file_not_found_if_file_does_not_exists(void);

static test_result all_tests(void) {
    should_get_file_not_found_if_file_does_not_exists();
    return EXIT_SUCCESS;
}

static test_result should_get_file_not_found_if_file_does_not_exists(void) {
    return TEST_SUCCESS;
}

