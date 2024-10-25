add_executable(r-type_server
    main.cpp
    Game.cpp
    ../../ecs/src/CoreModule.cpp
    ../../ecs/src/managers/system/SystemManager.cpp
    ../../ecs/src/managers/component/ComponentManager.cpp
    ../../ecs/src/managers/entity/EntityManager.cpp
    ../../ecs/src/components/sprite/SpriteComponent.cpp
    ../../ecs/src/components/texture/TextureComponent.cpp
    ../../ecs/src/components/hitbox/HitBoxComponent.cpp
    ../../ecs/src/components/music/MusicComponent.cpp
    ../../ecs/src/components/sound/SoundComponent.cpp
    ../../ecs/src/components/input/InputComponent.cpp
    ../../ecs/src/components/velocity/VelocityComponent.cpp
    ../../ecs/src/components/transform/TransformComponent.cpp
    ../../ecs/src/components/health/HealthComponent.cpp
    ../../ecs/src/components/damage/DamageComponent.cpp
    ../../ecs/src/components/parent/ParentComponent.cpp
    ../../ecs/src/components/type/TypeComponent.cpp
    ../../ecs/src/components/cooldown/CooldownComponent.cpp
    ../../ecs/src/components/weapon/WeaponComponent.cpp
    ../../ecs/src/components/size/SizeComponent.cpp
    ../../ecs/src/entity/Entity.cpp
)


target_link_libraries(r-type_server r-type_interfaces sfml-graphics sfml-window sfml-system)
target_include_directories(r-type_server PRIVATE ${SFML_INCLUDE_DIR})

add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_server> ${CMAKE_SOURCE_DIR}
)
