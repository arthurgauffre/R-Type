cmake_minimum_required(VERSION 3.10)

# Include the SFML package
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

project(R-TypeInterfacesGraphic
        VERSION 1.0
        DESCRIPTION "Interfaces graphics for the R-Type project"
        LANGUAGES CXX
)

add_library(r-type_interfaces_graphic INTERFACE)

# Specify the SFML include directory
target_include_directories(r-type_interfaces_graphic PRIVATE ${SFML_INCLUDE_DIR})

target_include_directories(r-type_interfaces_graphic
        INTERFACE "include"
)

target_link_libraries(
    r-type_interfaces_graphic
    INTERFACE sfml-graphics sfml-window
)
