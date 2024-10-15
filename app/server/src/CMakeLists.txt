add_executable(r-type_server
    main.cpp
    ../../ecs/src/CoreModule.cpp
    ../../ecs/src/managers/system/SystemManager.cpp
    # app/ecs/src/managers/system/SystemManager.cpp
    ../../ecs/src/managers/component/ComponentManager.cpp
    # app/ecs/src/managers/component/ComponentManager.cpp
    # app/ecs/src/managers/entity/EntityManager.cpp
    ../../ecs/src/managers/entity/EntityManager.cpp
    # app/ecs/src/components/sprite/SpriteComponent.cpp
    ../../ecs/src/components/sprite/SpriteComponent.cpp
    # app/ecs/src/components/texture/TextureComponent.cpp
    ../../ecs/src/components/texture/TextureComponent.cpp
    # app/ecs/src/components/position/PositionComponent.cpp
    ../../ecs/src/components/position/PositionComponent.cpp
    # app/ecs/src/components/hitbox/HitBoxComponent.cpp
    ../../ecs/src/components/hitbox/HitBoxComponent.cpp
    # app/ecs/src/components/music/MusicComponent.cpp
    ../../ecs/src/components/music/MusicComponent.cpp
    # app/ecs/src/components/sound/SoundComponent.cpp
    ../../ecs/src/components/sound/SoundComponent.cpp
    # app/ecs/src/components/input/InputComponent.cpp
    ../../ecs/src/components/input/InputComponent.cpp
    # app/ecs/src/components/velocity/VelocityComponent.cpp
    ../../ecs/src/components/velocity/VelocityComponent.cpp
    # app/ecs/src/components/transform/TransformComponent.cpp
    ../../ecs/src/components/transform/TransformComponent.cpp
    # app/ecs/src/components/background/BackgroundComponent.cpp
    ../../ecs/src/components/background/BackgroundComponent.cpp
    # app/ecs/src/components/scroll/ScrollComponent.cpp
    ../../ecs/src/components/scroll/ScrollComponent.cpp
    # app/ecs/src/components/health/HealthComponent.cpp
    ../../ecs/src/components/health/HealthComponent.cpp
    # app/ecs/src/entity/Entity.cpp
    ../../ecs/src/entity/Entity.cpp
)

# target_link_libraries(r-type_server r-type_interfaces r-type_server_interfaces)

target_link_libraries(r-type_server r-type_interfaces r-type_server_interfaces sfml-graphics sfml-window sfml-system)
target_include_directories(r-type_server PRIVATE ${SFML_INCLUDE_DIR})

add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_server> ${CMAKE_SOURCE_DIR}
)
