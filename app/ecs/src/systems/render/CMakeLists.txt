set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_library(r-type_render_system SHARED
    RenderSystem.cpp
    ../../components/sprite/SpriteComponent.cpp
    ../../components/texture/TextureComponent.cpp
    ../../components/transform/TransformComponent.cpp
    ../../components/hitbox/HitBoxComponent.cpp
    ../../components/size/SizeComponent.cpp
    ../../components/type/TypeComponent.cpp
)

target_include_directories(r-type_render_system PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(
    r-type_render_system
    r-type_interfaces
    sfml-graphics
)
