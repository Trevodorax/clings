project(katas C)

add_library(katas katas.c)
target_include_directories(types PUBLIC ..)

add_executable(katas_test
        katas_test.c
        katas.c
        ../types/mocks.c
)

add_test(NAME katas_test COMMAND katas_test)