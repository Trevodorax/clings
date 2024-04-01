
#include "CUnit/Basic.h"
#include "yaml_parser_factory.h"
#include "yml.h"


static FILE* temp_file = NULL;
static char* file_path = "temp.yml";

void clear_file(void) {
    if(temp_file != NULL) {
        freopen(file_path, "w+", temp_file);
    }
}

int init_suite(void) {
    if (NULL == (temp_file = fopen(file_path, "w+")))
        return -1;
    else
        return 0;
}

yaml_parser_t init_test(const char* yaml) {
    clear_file();

    fprintf(temp_file, "%s", yaml);

    rewind(temp_file);
    yaml_parser_t parser;
    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, temp_file);

    return parser;
}

int clean(void) {
    if (0 != fclose(temp_file)) {
        return -1;
    }
    else {
        temp_file = NULL;
        return 0;
    }
}

void test_parser_factory(void) {
    yaml_parser_t parser = parser_factory(file_path);
    CU_ASSERT(parser.error == YAML_NO_ERROR);
    yaml_parser_delete(&parser);
}

void test_parser_factory_with_bad_path(void) {
    yaml_parser_t parser = parser_factory("bad/path/file.yml");
    CU_ASSERT(parser.error == YAML_READER_ERROR);
    CU_ASSERT_STRING_EQUAL(parser.problem, "Failed to open yaml file.");
    yaml_parser_delete(&parser);
}

void test_parse_exercises(void) {

    yaml_parser_t parser = init_test("exercises:\n"
                                     "  - name: intro\n"
                                     "    path: katas/intro.c\n"
                                     "\n"
                                     "  - name: success\n"
                                     "    path: katas/success.c\n");
    kata_list_query_result_t res = parse_kata_list(&parser);

    CU_ASSERT_TRUE_FATAL(res.success);
    CU_ASSERT_EQUAL_FATAL(res.kata_list.len, 2);
    CU_ASSERT_STRING_EQUAL(res.kata_list.katas[0].name.str, "intro");
    CU_ASSERT_STRING_EQUAL(res.kata_list.katas[0].path.str, "katas/intro.c");
    CU_ASSERT_STRING_EQUAL(res.kata_list.katas[1].name.str, "success");
    CU_ASSERT_STRING_EQUAL(res.kata_list.katas[1].path.str, "katas/success.c");
}

void test_parse_no_exercises_found(void) {
    yaml_parser_t parser = init_test("exercises:\n");
    kata_list_query_result_t res = parse_kata_list(&parser);

    CU_ASSERT_TRUE_FATAL(res.success);
    CU_ASSERT_EQUAL_FATAL(res.kata_list.len, 0);
}

void test_parse_exercise_missing_name(void) {
    yaml_parser_t parser = init_test("exercises:\n"
                                     "  - path: katas/intro.c\n");
    kata_list_query_result_t res = parse_kata_list(&parser);

    CU_ASSERT_FALSE_FATAL(res.success);
    CU_ASSERT_STRING_EQUAL(res.error_message, "Failed to parse file yaml.");
}

void test_parse_exercise_typo_in_path_key(void) {

    yaml_parser_t parser = init_test("exercises:\n"
                                     "  - name: intro\n"
                                     "    path: katas/intro.c\n"
                                     "\n"
                                     "  - name: success\n"
                                     "    pathTYPO: katas/success.c\n");
    kata_list_query_result_t res = parse_kata_list(&parser);

    CU_ASSERT_FALSE_FATAL(res.success);
    CU_ASSERT_STRING_EQUAL(res.error_message, "Failed to parse file yaml.");
}

void test_parse_exercise_typo_in_exercises(void) {

    yaml_parser_t parser = init_test("other:\n"
                                     "  - name: intro\n"
                                     "    path: katas/intro.c\n");
    kata_list_query_result_t res = parse_kata_list(&parser);

    CU_ASSERT_FALSE_FATAL(res.success);
    CU_ASSERT_STRING_EQUAL(res.error_message, "Exercises not found.");
}

int main(void) {
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite = CU_add_suite("Yaml", init_suite, clean);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(pSuite, "given file exists", test_parser_factory);
    CU_add_test(pSuite, "given file does not exist", test_parser_factory_with_bad_path);
    CU_add_test(pSuite, "yaml with two exercises", test_parse_exercises);
    CU_add_test(pSuite, "yaml with zero exercises", test_parse_no_exercises_found);
    CU_add_test(pSuite, "yaml with missing exercise name", test_parse_exercise_missing_name);
    CU_add_test(pSuite, "yaml with typo in key", test_parse_exercise_typo_in_path_key);
    CU_add_test(pSuite, "yaml with typo in exercises sequence", test_parse_exercise_typo_in_exercises);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    int failures = (int) CU_get_number_of_failures();
    CU_cleanup_registry();
    return failures;
}
