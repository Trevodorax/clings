#ifndef CLINGS_EXECUTION_ERRORS_H
#define CLINGS_EXECUTION_ERRORS_H

#include "katas/katas.h"

run_kata_result_t kata_not_found(kata_t kata);

run_kata_result_t compilation_failed(kata_t kata, sized_string_t output_error);

run_kata_result_t execution_failed(kata_t kata, sized_string_t output_error);

run_kata_result_t open_process_failed(kata_t kata, sized_string_t command);

#endif //CLINGS_EXECUTION_ERRORS_H
