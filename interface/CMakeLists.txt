cmake_minimum_required(VERSION 3.10)

# Include the SFML package

project(R-TypeInterfaces
        VERSION 1.0
        DESCRIPTION "Interfaces for the R-Type project"
        LANGUAGES CXX
)

add_library(r-type_interfaces INTERFACE)

# Specify the SFML include directory
target_include_directories(r-type_interfaces PRIVATE ${SFML_INCLUDE_DIR})

target_include_directories(r-type_interfaces
        INTERFACE "include"
)

target_link_libraries(
    r-type_interfaces
    INTERFACE sfml-graphics sfml-window sfml-system sfml-audio
)
