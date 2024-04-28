#ifndef CLINGS_EXECUTION_H
#define CLINGS_EXECUTION_H

#include "types/types.h"
#include "katas/katas.h"
#define MAX_PATH_LENGTH 1024
#define COMPILE_COMMAND "gcc -o /tmp/kata %s"
#define RUN_COMMAND "/tmp/kata"

/**
 * @brief Runs the kata at given index, and handles the result
 *
 * @param kata The kata to run (cf. katas.h)
 * @param result_buffer String in which to write the result
 * @return The result status of the kata
 */
kata_status run_kata(kata_t kata, sized_string_t result_buffer);

#endif //CLINGS_EXECUTION_H
