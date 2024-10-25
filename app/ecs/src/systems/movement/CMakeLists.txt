# Include the SFML package
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_library(r-type_movement_system SHARED
    MovementSystem.cpp
    ../../components/transform/TransformComponent.cpp
    ../../components/size/SizeComponent.cpp
    ../../components/type/TypeComponent.cpp
    ../../components/velocity/VelocityComponent.cpp
)

# Specify the SFML include directory
target_include_directories(r-type_movement_system PRIVATE ${SFML_INCLUDE_DIR})

# Link the SFML library
target_link_libraries(
    r-type_movement_system
    r-type_interfaces
)
