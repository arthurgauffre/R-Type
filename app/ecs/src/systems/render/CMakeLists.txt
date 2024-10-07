add_library(r-type_render_system SHARED
    RenderSystem.cpp
)

# Specify the SFML include directory
target_include_directories(r-type_render_system PRIVATE ${SFML_INCLUDE_DIR})

# Link the SFML library
target_link_libraries(
    r-type_render_system
    r-type_interfaces
    sfml-graphics
)
