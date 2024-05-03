project(execution C)

add_library(execution execution.c
        execution_errors.h
        execution_errors.c)
target_include_directories(execution PUBLIC ..)

add_executable(execution_test
        execution_test.c
        execution.c
        execution_errors.h
        execution_errors.c
)

add_test(NAME execution_test COMMAND execution_test)