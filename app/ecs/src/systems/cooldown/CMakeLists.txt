cmake_minimum_required(VERSION 3.10)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(r-type_cooldown_system SHARED
    CooldownSystem.cpp
    ../../components/cooldown/CooldownComponent.cpp
)

target_link_libraries(
    r-type_cooldown_system
    r-type_interfaces
)

target_link_libraries(r-type_cooldown_system)
