#include <stdio.h>
#include "result_handler.h"
#include "stdbool.h"

bool isStatusError(kata_status status) {
    switch (status) {
        case KATA_COMPILATION_FAILURE:
        case KATA_EXECUTION_FAILURE:
        case KATA_TEST_FAILURE:
        case KATA_ERROR: return true;
        default: return false;
    }
}

void handle_kata_result(run_kata_result_t result) {

    FILE * out = isStatusError(result.status) ? stderr : stdout;
    if (result.output.str && result.output.len > 0) {
        fprintf(out, "%s", result.output.str);
    }

    printf("\n");
}
