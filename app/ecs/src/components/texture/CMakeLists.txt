add_library(r-type_texture_component SHARED
    TextureComponent.cpp
)

target_link_libraries(
    r-type_texture_component
    r-type_interfaces
    -lsfml-graphics
)
