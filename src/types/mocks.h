#ifndef CLINGS_MOCKS_H
#define CLINGS_MOCKS_H

#include "stdio.h"

/**
 * Typedef for a function pointer implementing the behavior of the calloc function.
 *
 * Functions matching this typedef are expected to allocate memory for an array
 * of 'count' objects, each 'size' bytes in size. The memory is initialized to zero.
 * The function returns a pointer to the allocated memory if the allocation is successful.
 * If the allocation fails, the function returns NULL and sets the errno to ENOMEM.
 *
 * The main use of this typedef is to mock the calloc function for testing.
 *
 * @param count Number of elements to allocate memory for.
 * @param size Size of each element in bytes.
 * @return Pointer to the allocated memory block if successful; otherwise, NULL.
 */
typedef void *(*calloc_f)(size_t count, size_t size);

/**
 * @brief Get the implementation of calloc_f which always returns NULL.
 * @return NULL
 */
calloc_f failing_calloc(void);

/**
 * Typedef for a function pointer implementing the behavior of the realloc function.
 *
 * Functions matching this typedef are expected to reallocate memory as specified by realloc,
 * possibly moving it to a new location. The function returns a pointer to the newly
 * allocated memory if the reallocation is successful. If the reallocation fails,
 * the function returns NULL and sets the errno to ENOMEM.
 *
 * The main use of this typedef is to mock the realloc function for testing.
 *
 * @param ptr Pointer to the memory block previously allocated with malloc, calloc, or realloc.
 * @param size New size in bytes for the memory block.
 * @return Pointer to the reallocated memory block if successful; otherwise, NULL.
 */
typedef void *(*realloc_f)(void * ptr, size_t size);

/**
 * @brief Get the implementation of realloc_f which always returns NULL.
 * @return NULL
 */
realloc_f failing_realloc(void);

/**
 * Typedef for a function pointer implementing the behavior of the fopen function.
 *
 * Functions matching this typedef are expected to open the file specified by 'filename'
 * with the mode specified by 'mode'. If successful, the function returns a pointer to
 * a FILE* associated with the opened file. If the file cannot be opened or an error occurs,
 * the function returns NULL and sets the errno to indicate the error condition.
 *
 * The main use of this typedef is to mock the fopen function for testing.
 *
 * @param filename C string containing the name of the file to be opened.
 * @param mode C string containing a file access mode. [ r/w/a(+)(b/t) ]
 * @return Pointer to a FILE object associated with the opened file if successful; otherwise, NULL.
 */
typedef FILE *(*fopen_f)(const char *filename, const char *mode);

/**
 * @brief Get the implementation of fopen_f which always returns NULL.
 * @return NULL
 */
fopen_f failing_fopen(void);

/**
 * @brief Get the implementation of fopen_f which open a FILE * from a buffer in memory.
 * @return FILE * of a buffer in memory.
 */
fopen_f memory_fopen(void);

/**
 * Typedef for a function pointer implementing the behavior of the popen function.
 *
 * Functions matching this typedef are expected to execute the specified shell command
 * with the given mode. The mode determines whether the command should be executed for
 * reading or writing. If successful, the function returns a pointer to a FILE* that
 * represents a stream associated with the executed command. If the command cannot be executed
 * or an error occurs, the function returns NULL and sets the errno to indicate the error condition.
 *
 * The main use of this typedef is to mock the popen function for testing.
 *
 * @param command C string containing the command to be executed by the shell.
 * @param mode C string containing a file access mode ("r" or "w").
 * @return Pointer to a FILE object representing a stream associated with the executed command
 * if successful; otherwise, NULL.
 */
typedef FILE *(*popen_f)(const char *command, const char *mode);

/**
 * @brief Get the implementation of popen_f which always returns NULL.
 * @return NULL
 */
popen_f failing_popen(void);

/**
 * @brief Get the implementation of popen_f which open a FILE * from a buffer in memory.
 * @return FILE * of a buffer in memory.
 */
popen_f memory_popen(void);


/**
 * Typedef for a function pointer implementing the behavior of the pclose function.
 *
 * Functions matching this typedef are expected to close a stream opened by the popen function.
 * The function waits for the associated command to terminate and returns the termination
 * status of the command as returned by the waitpid function. If an error occurs, the function
 * returns -1 and sets the errno to indicate the error condition.
 *
 * The main use of this typedef is to mock the pclose function for testing.
 *
 * @param stream Pointer to a FILE object representing a stream opened by popen.
 * @return The termination status of the command if successful; otherwise, -1.
 */
typedef int (*pclose_f)(FILE *stream);

/**
 * @brief Get the implementation of pclose_f which always returns EXIT_FAILURE.
 * @return EXIT_FAILURE
 */
pclose_f failing_pclose(void);

/**
 * @brief Get the implementation of pclose_f which always returns EXIT_SUCCESS.
 * @return EXIT_SUCCESS
 */
pclose_f success_pclose(void);

#endif //CLINGS_MOCKS_H
