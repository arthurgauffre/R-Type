add_library(r-type_texture_component SHARED
    TextureComponent.cpp
)

# Specify the SFML include directory
target_include_directories(r-type_texture_component PRIVATE ${SFML_INCLUDE_DIR})

# Link the SFML library
target_link_libraries(
    r-type_texture_component
    r-type_interfaces
    sfml-graphics
)
