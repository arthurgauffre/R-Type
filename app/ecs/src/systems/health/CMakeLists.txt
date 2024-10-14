add_library(r-type_health_system SHARED
    HealthSystem.cpp
    ../../components/health/HealthComponent.cpp
)

target_include_directories(r-type_health_system PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(
    r-type_health_system
    r-type_interfaces
)
