set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(r-type_server_system SHARED
    ServerSystem.cpp
    ../../Clock.cpp
    ../../managers/system/SystemManager.cpp
    ../../managers/component/ComponentManager.cpp
    ../../managers/entity/EntityManager.cpp
    ../../components/sprite/SpriteComponent.cpp
    ../../components/texture/TextureComponent.cpp
    ../../components/hitbox/HitBoxComponent.cpp
    ../../components/music/MusicComponent.cpp
    ../../components/sound/SoundComponent.cpp
    ../../components/input/InputComponent.cpp
    ../../components/velocity/VelocityComponent.cpp
    ../../components/transform/TransformComponent.cpp
    ../../components/health/HealthComponent.cpp
    ../../components/damage/DamageComponent.cpp
    ../../components/parent/ParentComponent.cpp
    ../../components/type/TypeComponent.cpp
    ../../components/cooldown/CooldownComponent.cpp
    ../../components/size/SizeComponent.cpp
    ../../components/ai/AIComponent.cpp
    ../../components/rectangle/RectangleShapeComponent.cpp
    ../../components/onclick/OnClickComponent.cpp
    ../../components/text/TextComponent.cpp
    ../../entity/Entity.cpp
)

target_link_libraries(
    r-type_server_system
    r-type_interfaces
)
