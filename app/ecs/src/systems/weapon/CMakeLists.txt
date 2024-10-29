set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(r-type_weapon_system SHARED
    WeaponSystem.cpp
    ../../components/damage/DamageComponent.cpp
    ../../components/parent/ParentComponent.cpp
    ../../components/weapon/WeaponComponent.cpp
    ../../components/cooldown/CooldownComponent.cpp
    ../../components/velocity/VelocityComponent.cpp
    ../../components/texture/TextureComponent.cpp
    ../../components/type/TypeComponent.cpp
    ../../components/transform/TransformComponent.cpp
    ../../components/hitbox/HitBoxComponent.cpp
    ../../components/sound/SoundComponent.cpp
    ../../managers/entity/EntityManager.cpp
    ../../entity/Entity.cpp
)

target_include_directories(r-type_weapon_system PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(
    r-type_weapon_system
    r-type_interfaces
)
