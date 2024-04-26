project(clings_configuration C)

add_library(configuration get_kata_list/in_memory_kata_list.c)
target_include_directories(configuration PUBLIC ..)