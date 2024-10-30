add_library(r-type_graphic_system SHARED
    SfmlGraphic.cpp
)

target_include_directories(r-type_graphic_system PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(
    r-type_graphic_system
    r-type_interfaces
    sfml-audio
    sfml-graphics
)
