cmake_minimum_required(VERSION 3.10)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(r-type_collision_system SHARED
    CollisionSystem.cpp
    ../../components/hitbox/HitBoxComponent.cpp
    ../../components/health/HealthComponent.cpp
    ../../components/type/TypeComponent.cpp
    ../../components/damage/DamageComponent.cpp
    ../../components/velocity/VelocityComponent.cpp
)

target_link_libraries(
    r-type_collision_system
    r-type_interfaces
)

target_link_libraries(r-type_collision_system)
