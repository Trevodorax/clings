project(clings_configuration C)


add_library(configuration
        get_kata_list/yaml_kata_list.c
)

add_subdirectory(get_kata_list/yaml)
target_link_libraries(configuration PUBLIC clings_yaml)
