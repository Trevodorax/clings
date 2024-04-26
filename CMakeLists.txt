cmake_minimum_required(VERSION 3.26)
project(clings C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic -Wconversion")

add_subdirectory(src/configuration)
add_subdirectory(src/types)

add_executable(clings main.c
        src/execution/execution.c
        src/result_handler/result_handler.c
        src/clings.c
        src/katas/katas.c
)

if(NOT ${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    file(COPY katas DESTINATION ${CMAKE_BINARY_DIR})
endif ()

target_include_directories(clings PUBLIC src)
target_link_libraries(clings PUBLIC configuration)
target_link_libraries(clings PUBLIC types)


add_subdirectory(src/test_utils)
target_link_libraries(sized_string_test PUBLIC test_utils)