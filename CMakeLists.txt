cmake_minimum_required(VERSION 3.26)
project(clings C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")

include_directories(src)
add_subdirectory(src/configuration)

add_executable(clings main.c
        src/execution/execution.c
        src/types/sized_string.c
        src/result_handler/result_handler.c
        src/clings.c
        src/katas/katas.c
)

if(NOT ${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    file(COPY info.yml DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY katas DESTINATION ${CMAKE_BINARY_DIR})
endif ()

target_link_libraries(clings PUBLIC configuration)