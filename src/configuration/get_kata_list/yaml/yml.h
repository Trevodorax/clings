#ifndef CLINGS_YML_H
#define CLINGS_YML_H

#include <yaml.h>
#include "katas/katas.h"
#include "stdbool.h"

/**
 * @brief Parse a YAML stream and extract a list of katas.
 *
 * This function parses a YAML stream using the provided YAML parser and extracts
 * a list of katas. It iterates through the YAML events, looking for sequences
 * and calls the `parse_kata` function to extract individual katas. Valid katas
 * (those with non-empty names and paths) are added to the resulting kata list.
 *
 * @param parser The YAML parser to use for parsing the stream.
 * @return A kata_list_query_result_t structure representing the result of the parsing operation.
 *         The structure contains a success flag and the parsed kata list.
 *         If an error occurs during parsing, the success flag will be false.
 */
kata_list_query_result_t parse_kata_list(yaml_parser_t *parser);

#endif //CLINGS_YML_H
