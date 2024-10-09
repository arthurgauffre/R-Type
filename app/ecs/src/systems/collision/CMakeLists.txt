add_library(r-type_collision_system SHARED
    CollisionSystem.cpp
    ../../components/hitbox/HitBoxComponent.cpp
)

target_include_directories(r-type_collision_system PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(
    r-type_collision_system
    r-type_interfaces
)
