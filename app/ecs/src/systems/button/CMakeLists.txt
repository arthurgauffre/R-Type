cmake_minimum_required(VERSION 3.10)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(r-type_button_system SHARED
    ButtonSystem.cpp
    ../../components/onclick/OnClickComponent.cpp
    ../../components/transform/TransformComponent.cpp
    ../../components/rectangle/RectangleShapeComponent.cpp
)

target_link_libraries(
    r-type_button_system
    r-type_interfaces
)
