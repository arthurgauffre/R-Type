set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(r-type_render_system SHARED
    RenderSystem.cpp
    ../../components/sprite/SpriteComponent.cpp
    ../../components/texture/TextureComponent.cpp
    ../../components/transform/TransformComponent.cpp
    ../../components/hitbox/HitBoxComponent.cpp
    ../../components/size/SizeComponent.cpp
    ../../components/type/TypeComponent.cpp
    ../../components/rectangle/RectangleShapeComponent.cpp
    ../../components/text/TextComponent.cpp
)

target_link_libraries(
    r-type_render_system
    r-type_interfaces
)
