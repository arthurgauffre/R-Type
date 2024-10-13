add_library(r-type_component_manager SHARED
    ComponentManager.cpp
    ../../components/hitbox/HitBoxComponent.cpp
    ../../components/sprite/SpriteComponent.cpp
    ../../components/texture/TextureComponent.cpp
    ../../components/position/PositionComponent.cpp
    ../../components/music/MusicComponent.cpp
    ../../components/sound/SoundComponent.cpp
    ../../components/input/InputComponent.cpp
    ../../components/velocity/VelocityComponent.cpp
    ../../components/transform/TransformComponent.cpp
)

target_link_libraries(
    r-type_component_manager
    r-type_interfaces
)
