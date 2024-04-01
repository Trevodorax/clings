#include <yaml.h>
#include "stdbool.h"
#include "types/types.h"
#include "katas/katas.h"

typedef struct key_value_parsed {
    sized_string_t key;
    sized_string_t value;
} key_value_parsed_t;

key_value_parsed_t parse_key_value(yaml_parser_t *parser, yaml_event_t *event);

kata_t parse_kata(yaml_parser_t *parser, yaml_event_t *event);

kata_list_fetch_result_t kata_list_parsing_error(void);

void free_key_value_parsed(key_value_parsed_t *key_value_parsed);

kata_list_fetch_result_t parse_kata_list_from_sequence(yaml_parser_t *parser, yaml_event_t *event);

/**
 * @brief Parse the next event from the parser and store it in the event pointer.
 * If the parsing failed, the parser and the event are deleted.
 */
bool yaml_parse_next(yaml_parser_t * parser, yaml_event_t * event);

kata_list_fetch_result_t parse_kata_list(yaml_parser_t * parser) {
    yaml_event_t event;
    kata_list_t kata_list = {.katas = NULL, .len = 0};
    while (true) {
        if (!yaml_parse_next(parser, &event)) return kata_list_parsing_error();
        if (event.type == YAML_NO_EVENT) break;

        if (event.type == YAML_SEQUENCE_START_EVENT) {
            while (event.type != YAML_NO_EVENT && event.type != YAML_SEQUENCE_END_EVENT) {
                kata_t kata = parse_kata(parser, &event);
                if (kata.name.len != 0 && kata.path.len != 0)
                    push_kata_in_list(kata, &kata_list);
            }
        }
    }
    yaml_event_delete(&event);
    return (kata_list_fetch_result_t) {
            .success = true,
            .kata_list = kata_list
    };
}

bool yaml_parse_next(yaml_parser_t *parser, yaml_event_t *event) {
    bool success = yaml_parser_parse(parser, event);
    if (!success) {
        yaml_parser_delete(parser);
        yaml_event_delete(event);
    }
    return success;
}

kata_list_fetch_result_t kata_list_parsing_error(void) {
    return (kata_list_fetch_result_t) {
            .success = false,
            .error_message = "Failed to parse file yaml."
    };
}

kata_t parse_kata(yaml_parser_t *parser, yaml_event_t *event) {
    kata_t kata = no_kata();
    if (!yaml_parse_next(parser, event) || event->type != YAML_MAPPING_START_EVENT) return no_kata();

    key_value_parsed_t name = parse_key_value(parser, event);
    if (!name.key.str || strcmp(name.key.str, "name") != 0) {
        free_key_value_parsed(&name);
        return no_kata();
    }
    kata.name = name.value;

    key_value_parsed_t path = parse_key_value(parser, event);
    if (!path.key.str || strcmp(path.key.str, "path") != 0) {
        free_key_value_parsed(&name);
        free_key_value_parsed(&path);
        return no_kata();
    }
    kata.path = path.value;

    if (!yaml_parse_next(parser, event) || event->type != YAML_MAPPING_END_EVENT) {
        free_key_value_parsed(&name);
        free_key_value_parsed(&path);
        return no_kata();
    }

    free_sized_string(&name.key);
    free_sized_string(&path.key);
    return kata;
}

key_value_parsed_t parse_key_value(yaml_parser_t *parser, yaml_event_t *event) {
    key_value_parsed_t not_parsed = {.key = empty_sized_string(), .value = empty_sized_string()};

    // key
    if (!yaml_parser_parse(parser, event) || event->type != YAML_SCALAR_EVENT) return not_parsed;
    sized_string_t key = copy_str_to_sized_string((char *) event->data.scalar.value, event->data.scalar.length);

    // value
    if (!yaml_parser_parse(parser, event) || event->type != YAML_SCALAR_EVENT) {
        free_sized_string(&key);
        return not_parsed;
    }
    sized_string_t value = copy_str_to_sized_string((char *) event->data.scalar.value, event->data.scalar.length);

    if (key.len == 0 || value.len == 0) {
        free_sized_string(&key);
        free_sized_string(&value);
        return not_parsed;
    }
    return (key_value_parsed_t) {.key = key, .value = value};
}

void free_key_value_parsed(key_value_parsed_t *key_value_parsed) {
    free_sized_string(&key_value_parsed->key);
    free_sized_string(&key_value_parsed->value);
}
