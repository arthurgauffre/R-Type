cmake_minimum_required(VERSION 3.10)

add_subdirectory(include/graphics)
add_subdirectory(include/audios)

project(R-TypeInterfaces
        VERSION 1.0
        DESCRIPTION "Interfaces for the R-Type project"
        LANGUAGES CXX
)

add_library(r-type_interfaces INTERFACE)


target_include_directories(r-type_interfaces
        INTERFACE "include"
)

target_link_libraries(
    r-type_interfaces
    INTERFACE r-type_interfaces_graphic r-type_interfaces_audio
)
