#ifndef CLINGS_EXECUTION_H
#define CLINGS_EXECUTION_H

#include "types/types.h"
#include "katas/katas.h"

#define MAX_PATH_LENGTH 1024
#define RUN_COMMAND "/tmp/kata"
#define COMPILE_COMMAND "gcc -o %s %s 2>&1"


/**
 * Typedef for a function pointer implementing the behavior of a kata compiler.
 *
 * Functions matching this typedef are expected to compile the kata. The function
 * uses the popen and pclose functions provided to execute the compilation of the
 * kata code. The result of the kata compilation is returned as a run_kata_result_t structure.
 *
 * The main use of this typedef is to mock the kata compiler for testing.
 *
 * @see macro run_kata which define the default compiler_f used.
 *
 * @param kata A kata_t structure representing the kata to be compiled and executed.
 * @param popen A function pointer conforming to the popen_f typedef for opening a process.
 * @param pclose A function pointer conforming to the pclose_f typedef for closing a process.
 * @return A run_kata_result_t structure containing the results of the kata compilation.
 */
typedef run_kata_result_t (*compiler_f )(kata_t kata, popen_f popen, pclose_f pclose);

/**
 * @brief Default implementation of compiler_f
 *
 * @param kata A kata_t structure representing the kata to be compiled and executed.
 * @param popen A function pointer conforming to the popen_f typedef for opening a process.
 * @param pclose A function pointer conforming to the pclose_f typedef for closing a process.
 * @return A run_kata_result_t structure containing the results of the kata compilation.
 */
run_kata_result_t compile_with_popen_and_pclose(kata_t kata, popen_f popen, pclose_f pclose);


/**
 * Typedef for a function pointer implementing the behavior of a kata runner.
 *
 * Functions matching this typedef are expected to run the kata. The function
 * uses the popen and pclose functions provided to execute the compiled kata.
 * The result of the kata execution is returned as a run_kata_result_t structure.
 *
 * The main use of this typedef is to mock the kata runner for testing.
 *
 * @see macro run_kata which define the default runner_f used.
 *
 * @param compilation A kata_t run_kata_result_t representing the compiled kata.
 * @param popen A function pointer conforming to the popen_f typedef for opening a process.
 * @param pclose A function pointer conforming to the pclose_f typedef for closing a process.
 * @return A run_kata_result_t structure containing the results of the kata execution.
 */
typedef run_kata_result_t (*runner_f)(run_kata_result_t compilation, popen_f popen, pclose_f pclose);

/**
 * @brief Default implementation of runner_f
 *
 * @param compilation A kata_t run_kata_result_t representing the compiled kata.
 * @param popen A function pointer conforming to the popen_f typedef for opening a process.
 * @param pclose A function pointer conforming to the pclose_f typedef for closing a process.
 * @return A run_kata_result_t structure containing the results of the kata execution.
 */
run_kata_result_t run_with_popen_and_pclose(run_kata_result_t compilation, popen_f popen, pclose_f pclose);


/**
 * Structure containing function pointers for file and process handling.
 *
 * This structure aggregates function pointers for handling files and processes.
 * Specifically, it provides pointers to functions that implement file opening,
 * process opening, and process closing.
 *
 * Members:
 * - fopen: A function pointer conforming to the fopen_f typedef for opening files.
 * - popen: A function pointer conforming to the popen_f typedef for opening processes.
 * - pclose: A function pointer conforming to the pclose_f typedef for closing processes.
 *
 * The main use of this structure is to inject these function pointers to allow for
 * mocking and testing of components that depend on file and process operations.
 */
typedef struct infrastructure {
    fopen_f fopen;
    popen_f popen;
    pclose_f pclose;
} infrastructure_t;

/**
 * @brief Executes a kata using the provided compiler and runner functions, utilizing the specified infrastructure.
 *
 * This function compiles and runs a kata using the provided compiler and runner functions.
 * It uses the infrastructure functions for file and process handling to facilitate the
 * compilation and execution processes. The function returns a run_kata_result_t structure
 * containing the results of the kata execution.
 *
 * @param kata The kata_t structure representing the kata to be compiled and executed. (cf. katas.h)
 * @param compiler A function pointer conforming to the compiler_f typedef to compile the kata.
 * @param runner A function pointer conforming to the runner_f typedef to run the compiled kata.
 * @param infrastructure An infrastructure_t structure containing the function pointers for
 *                       file and process handling needed for compilation and execution.
 * @return A run_kata_result_t structure containing the results of the kata execution.
 */
run_kata_result_t
run_kata_with_compiler_and_runner(kata_t kata, compiler_f compiler, runner_f runner, infrastructure_t infrastructure);

/**
 * A macro defining the default infrastructure for file and process handling.
 *
 * This macro initializes an infrastructure_t structure with the default
 * function pointers for file and process handling, using the standard fopen,
 * popen, and pclose functions.
 */
#define default_infrastructure (infrastructure_t) {.fopen = &fopen, .popen = &popen, .pclose = &pclose}

/**
 * A macro to run a kata with the default compiler and runner.
 *
 * @param kata The kata_t structure representing the kata to be executed.
 * @return A run_kata_result_t structure containing the results of the kata execution.
 *
 * Example:
 * run_kata_result_t result = run_kata(my_kata);
 */
#define run_kata(kata) run_kata_with_compiler_and_runner(kata, &compile_with_popen_and_pclose, &run_with_popen_and_pclose, default_infrastructure)


#endif //CLINGS_EXECUTION_H
