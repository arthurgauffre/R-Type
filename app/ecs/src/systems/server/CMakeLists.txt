# Include the SFML package
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_library(r-type_server_system SHARED
    ServerSystem.cpp
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
    ../../components/type/TypeComponent.cpp
    ../../entity/Entity.cpp
)

# Specify the SFML include directory
target_include_directories(r-type_server_system PRIVATE ${SFML_INCLUDE_DIR})

# Link the SFML library
target_link_libraries(
    r-type_server_system
    r-type_interfaces
    sfml-graphics
)
