#include <stdio.h>
#include "result_handler.h"

void handle_kata_result(run_kata_result_t result) {

    if (result.output.str && result.output.len > 0) {
        printf("%s", result.output.str);
    }

    printf("\n");
}
