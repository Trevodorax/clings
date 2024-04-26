project(result_handler C)

add_library(result_handler result_handler.c)
target_include_directories(execution PUBLIC ..)