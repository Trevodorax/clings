#include "yaml_parser_factory.h"

yaml_parser_t parser_factory(char * file_path) {
    FILE *input = fopen(file_path, "rb");
    if (input == NULL) {
        return (yaml_parser_t) {
                .error = YAML_READER_ERROR,
                .problem = "Failed to open yaml file."
        };
    }
    yaml_parser_t parser;
    if(yaml_parser_initialize(&parser)) {
        yaml_parser_set_input_file(&parser, input);
    } else {
        return (yaml_parser_t) {
                .error = YAML_MEMORY_ERROR,
                .problem = "Failed to initialize yaml parser."
        };
    }

    return parser;
}
