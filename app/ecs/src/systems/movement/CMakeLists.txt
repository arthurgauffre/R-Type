set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(r-type_movement_system SHARED
    MovementSystem.cpp
    ../../components/transform/TransformComponent.cpp
    ../../components/size/SizeComponent.cpp
    ../../components/type/TypeComponent.cpp
    ../../components/size/SizeComponent.cpp
)

target_include_directories(r-type_movement_system PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(
    r-type_movement_system
    r-type_interfaces
)
