add_library(r-type_render_system SHARED
    RenderSystem.cpp
)

target_link_libraries(
    r-type_render_system
    r-type_interfaces
    -lsfml-graphics
)
