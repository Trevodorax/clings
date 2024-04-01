cmake_minimum_required(VERSION 3.26)
project(clings_yaml C)

find_package(yaml CONFIG REQUIRED)

add_library(clings_yaml
        yml.c
        yaml_parser_factory.c
)

target_link_libraries(clings_yaml PUBLIC yaml)