#include "get_kata_list.h"
#include "yaml/yaml_parser_factory.h"
#include "yaml/yml.h"


#define KATA_LIST_YAML_FILE_PATH "info.yml"

kata_list_fetch_result_t get_kata_list(void) {
    yaml_parser_t parser = parser_factory(KATA_LIST_YAML_FILE_PATH);
    const bool error = parser.error != YAML_NO_ERROR;
    if (error) {
        return (kata_list_fetch_result_t) {
                .success = false,
                .error_message= "Failed to open yaml file: " KATA_LIST_YAML_FILE_PATH "\n",
        };
    }

    kata_list_fetch_result_t kata_list_parsing_result = parse_kata_list(&parser);
    yaml_parser_delete(&parser);
    return kata_list_parsing_result;
}
