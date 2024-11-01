set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(r-type_sfml_graphic SHARED
    SfmlGraphic.cpp
)

target_include_directories(r-type_sfml_graphic PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(
    r-type_sfml_graphic
    r-type_interfaces
)
