#ifndef CLINGS_EXECUTION_H
#define CLINGS_EXECUTION_H

#include "types/types.h"
#include "katas/katas.h"

#define MAX_PATH_LENGTH 1024
#define RUN_COMMAND "/tmp/kata"
#define COMPILE_COMMAND "gcc -o %s %s 2>&1"


typedef run_kata_result_t (*compiler_f )(kata_t kata, popen_f popen, pclose_f pclose);

run_kata_result_t compile_with_popen_and_pclose(kata_t kata, popen_f popen, pclose_f pclose);


typedef run_kata_result_t (*runner_f)(run_kata_result_t compilation, popen_f popen, pclose_f pclose);

run_kata_result_t run_with_popen_and_pclose(run_kata_result_t compilation, popen_f popen, pclose_f pclose);

typedef struct infrastructure {
    fopen_f fopen;
    popen_f popen;
    pclose_f pclose;
} infrastructure_t;

/**
 * @brief Runs the kata
 *
 * @param kata The kata to runner (cf. katas.h)
 * @param result_buffer String in which to write the result
 * @return The result status of the kata
 */
run_kata_result_t
run_kata_with_compiler_and_runner(kata_t kata, compiler_f compiler, runner_f runner, infrastructure_t infrastructure);

#define default_infrastructure (infrastructure_t) {.fopen = &fopen, .popen = &popen, .pclose = &pclose}
#define run_kata(kata) run_kata_with_compiler_and_runner(kata, &compile_with_popen_and_pclose, &run_with_popen_and_pclose, default_infrastructure)


#endif //CLINGS_EXECUTION_H
