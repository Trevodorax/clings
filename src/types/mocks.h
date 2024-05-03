//
// Created by Théo Omnès on 03/05/2024.
//

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

#endif //CLINGS_MOCKS_H
