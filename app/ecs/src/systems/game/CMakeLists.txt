cmake_minimum_required(VERSION 3.10)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(r-type_game_system SHARED
    GameSystem.cpp
    ../../components/type/TypeComponent.cpp
)

target_link_libraries(
    r-type_game_system
    r-type_interfaces
)
