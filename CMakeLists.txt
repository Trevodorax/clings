cmake_minimum_required(VERSION 3.26)
project(clings C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic -Wconversion")

# copy katas in build directory
if(NOT ${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    file(COPY katas DESTINATION ${CMAKE_BINARY_DIR})
endif ()

add_executable(clings main.c
        src/clings.c
        src/execution/execution.c
        src/result_handler/result_handler.c
)
target_include_directories(clings PUBLIC src)
add_subdirectory(src/test_utils)

add_subdirectory(src/configuration)
target_link_libraries(clings PUBLIC configuration)
enable_testing()

add_subdirectory(src/types)
target_link_libraries(clings PUBLIC types)
target_link_libraries(sized_string_test PUBLIC test_utils)

add_subdirectory(src/katas)
target_link_libraries(clings PUBLIC katas)
target_link_libraries(katas PUBLIC types)
target_link_libraries(katas_test PUBLIC test_utils)
target_link_libraries(katas_test PUBLIC types)



