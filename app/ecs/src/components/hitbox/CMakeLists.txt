add_library(r-type_hitbox_component SHARED
    HitBoxComponent.cpp
)

target_link_libraries(
    r-type_hitbox_component
    r-type_interfaces
)
