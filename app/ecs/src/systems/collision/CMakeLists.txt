add_library(r-type_collision_system SHARED
    CollisionSystem.cpp
)

target_link_libraries(
    r-type_collision_system
    r-type_interfaces
)
