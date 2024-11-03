set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(r-type_ai_system SHARED
    AISystem.cpp
    ../../components/ai/AIComponent.cpp
    ../../components/type/TypeComponent.cpp
    ../../components/velocity/VelocityComponent.cpp
    ../../components/transform/TransformComponent.cpp
)

target_link_libraries(
    r-type_ai_system
    r-type_interfaces
)
