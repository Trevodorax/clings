#ifndef CLINGS_EXECUTION_H
#define CLINGS_EXECUTION_H

#include "types/types.h"
#include "katas/katas.h"
#define MAX_PATH_LENGTH 1024
#define RUN_COMMAND "/tmp/kata"
#define COMPILE_COMMAND "gcc -o RUN_COMMAND %s 2>&1"


/**
 * @brief Runs the kata
 *
 * @param kata The kata to run (cf. katas.h)
 * @param result_buffer String in which to write the result
 * @return The result status of the kata
 */
run_kata_result_t run_kata(kata_t kata);

#endif //CLINGS_EXECUTION_H
