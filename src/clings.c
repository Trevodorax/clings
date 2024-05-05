#include <printf.h>
#include "clings.h"
#include "types/types.h"
#include "execution/execution.h"
#include "result_handler/result_handler.h"
#include "katas/katas.h"
#include "configuration/get_kata_list/get_kata_list.h"

int clings(void) {
    const kata_list_fetch_result_t kata_list_fetch_result = get_kata_list();

    if (!kata_list_fetch_result.success) {
        fprintf(stderr, "Failed to retrieve kata list: %s\n", kata_list_fetch_result.error_message);
        return EXIT_FAILURE;
    }
    kata_list_t kata_list = kata_list_fetch_result.kata_list;

    bool no_kata = kata_list.len == 0;
    if (no_kata) {
        return EXIT_SUCCESS;
    }

    for (size_t i = 0; i < kata_list.len; i++) {
        kata_t kata = kata_list.katas[i];
        if (!kata.is_done) {
            run_kata_result_t result = run_kata(kata);
            handle_kata_result(result);
            free_sized_string(&result.output); // (free output == free error) <= same memory space <= union
            break;
        }
    }

    free_kata_list(&kata_list);

    return EXIT_SUCCESS;
}
