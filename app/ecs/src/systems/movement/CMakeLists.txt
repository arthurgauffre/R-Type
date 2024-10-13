add_library(r-type_movement_system SHARED
    MovementSystem.cpp
    ../../components/position/PositionComponent.cpp
    ../../components/velocity/VelocityComponent.cpp
    ../../components/transform/TransformComponent.cpp
)

# Specify the SFML include directory
target_include_directories(r-type_movement_system PRIVATE ${SFML_INCLUDE_DIR})

# Link the SFML library
target_link_libraries(
    r-type_movement_system
    r-type_interfaces
    sfml-graphics
)
