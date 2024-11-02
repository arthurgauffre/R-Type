set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(r-type_health_system SHARED
    HealthSystem.cpp
    ../../components/health/HealthComponent.cpp
)

target_link_libraries(
    r-type_health_system
    r-type_interfaces
)
