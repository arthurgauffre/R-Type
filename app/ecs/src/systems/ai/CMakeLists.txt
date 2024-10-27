add_library(r-type_ai_system SHARED
    AISystem.cpp
    ../../components/ai/AIComponent.cpp
    ../../components/type/TypeComponent.cpp
    ../../components/velocity/VelocityComponent.cpp
    ../../components/transform/TransformComponent.cpp
)

target_include_directories(r-type_ai_system PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(
    r-type_ai_system
    r-type_interfaces
)
