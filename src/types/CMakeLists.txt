project(types C)

add_library(types sized_string.c)
target_include_directories(types PUBLIC ..)

add_executable(sized_string_test
        sized_string_test.c
        sized_string.c
)

add_test(NAME sized_string_test COMMAND sized_string_test)