add_library(r-type_sprite_component SHARED
    SpriteComponent.cpp
)

# Specify the SFML include directory
target_include_directories(r-type_sprite_component PRIVATE ${SFML_INCLUDE_DIR})

# Link the SFML library
target_link_libraries(
    r-type_sprite_component
    r-type_interfaces
    sfml-graphics
)
