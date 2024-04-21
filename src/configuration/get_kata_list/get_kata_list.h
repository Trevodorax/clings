#ifndef CLINGS_GET_KATA_LIST_H
#define CLINGS_GET_KATA_LIST_H

#include "katas/katas.h"

/**
 * Retrieves a list of katas.
 *
 * This function fetch a list of all katas defined in the application and returns
 * a structure containing both the list itself and a status indicating whether the
 * list was successfully compiled. If an error occurs, the kata_list is set to NULL.
 * The list and the status are packaged in a kata_list_fetch_result_t struct.
 *
 * @return kata_list_fetch_result_t A struct containing:
 *         - 'success': a boolean indicating whether the katas were successfully retrieved.
 *         - 'kata_list': the list of katas fetched.
 */
kata_list_fetch_result_t get_kata_list(void);

#endif //CLINGS_GET_KATA_LIST_H
