#ifndef CLINGS_YAML_PARSER_FACTORY_H
#define CLINGS_YAML_PARSER_FACTORY_H

#include <yaml.h>

/**
 * @brief Create a YAML parser for a given file path.
 *
 * This function takes a file path as input, opens the file, and initializes a YAML parser
 * to parse the content of the file. If the file cannot be opened, an error is returned with
 * details about the failure. The resulting YAML parser can be used to parse the YAML content
 * from the specified file.
 *
 * @param file_path The path to the YAML file to be parsed.
 * @return A YAML parser initialized for the specified file path.
 *         If there is an error (e.g., file not found), the returned parser will have
 *         the error code set, and the problem description will provide details about the issue.
 */
yaml_parser_t parser_factory(char * file_path);

#endif //CLINGS_YAML_PARSER_FACTORY_H
