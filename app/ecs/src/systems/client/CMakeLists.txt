add_library(r-type_client_system SHARED
    ClientSystem.cpp
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
    ../../components/background/BackgroundComponent.cpp
    ../../components/health/HealthComponent.cpp
    ../../components/damage/DamageComponent.cpp
    ../../components/parent/ParentComponent.cpp
    ../../entity/Entity.cpp
)

target_include_directories(r-type_client_system PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(
    r-type_client_system
    r-type_interfaces
    sfml-audio
)
