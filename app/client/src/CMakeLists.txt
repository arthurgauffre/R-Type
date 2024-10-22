# add_executable(r-type_client
#     main.cpp
# )
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

if(SFML_FOUND)
    message(STATUS "SFML found: ${SFML_DIR}")
else()
    message(FATAL_ERROR "SFML not found")
endif()

add_executable(r-type_client
    main.cpp
    ../../ecs/src/CoreModule.cpp
    ../../ecs/src/managers/system/SystemManager.cpp
    ../../ecs/src/managers/component/ComponentManager.cpp
    ../../ecs/src/managers/entity/EntityManager.cpp
    ../../ecs/src/components/sprite/SpriteComponent.cpp
    ../../ecs/src/components/texture/TextureComponent.cpp
    ../../ecs/src/components/position/PositionComponent.cpp
    ../../ecs/src/components/hitbox/HitBoxComponent.cpp
    ../../ecs/src/components/music/MusicComponent.cpp
    ../../ecs/src/components/sound/SoundComponent.cpp
    ../../ecs/src/components/input/InputComponent.cpp
    ../../ecs/src/components/velocity/VelocityComponent.cpp
    ../../ecs/src/components/transform/TransformComponent.cpp
    ../../ecs/src/components/background/BackgroundComponent.cpp
    ../../ecs/src/components/scroll/ScrollComponent.cpp
    ../../ecs/src/components/health/HealthComponent.cpp
    ../../ecs/src/components/damage/DamageComponent.cpp
    ../../ecs/src/components/type/TypeComponent.cpp
    ../../ecs/src/components/weapon/WeaponComponent.cpp
    ../../ecs/src/components/cooldown/CooldownComponent.cpp
    ../../ecs/src/components/parent/ParentComponent.cpp
    ../../ecs/src/entity/Entity.cpp
)

target_link_libraries(r-type_client r-type_interfaces r-type_client_interfaces sfml-graphics sfml-window sfml-system)
target_include_directories(r-type_client PRIVATE ${SFML_INCLUDE_DIR})

add_custom_command(
    TARGET r-type_client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_client> ${CMAKE_SOURCE_DIR}
)

# Move .so files out of the build folder into the lib one
# set(LIB_DESTINATION ${CMAKE_SOURCE_DIR}/lib)
# set(LIB_COMPONENTS_DESTINATION ${LIB_DESTINATION}/components)
# set(LIB_SYSTEMS_DESTINATION ${LIB_DESTINATION}/systems)
# set(LIB_MANAGERS_DESTINATION ${LIB_DESTINATION}/managers)

# add_custom_command(
#   TARGET r-type_client
#   POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_music_component>
#           ${LIB_COMPONENTS_DESTINATION}/r-type_music_component.so)

# add_custom_command(
#   TARGET r-type_client
#   POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_sound_component>
#           ${LIB_COMPONENTS_DESTINATION}/r-type_sound_component.so)

# add_custom_command(
#   TARGET r-type_client
#   POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_component_manager>
#           ${LIB_MANAGERS_DESTINATION}/r-type_component_manager.so)

# add_custom_command(
#     TARGET r-type_client
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_entity_manager>
#             ${LIB_MANAGERS_DESTINATION}/r-type_entity_manager.so)

# add_custom_command(
#     TARGET r-type_client
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_sprite_component>
#             ${LIB_COMPONENTS_DESTINATION}/r-type_sprite_component.so)

# add_custom_command(
#     TARGET r-type_client
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_texture_component>
#             ${LIB_COMPONENTS_DESTINATION}/r-type_texture_component.so)

# add_custom_command(
#     TARGET r-type_client
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_system_manager>
#             ${LIB_MANAGERS_DESTINATION}/r-type_system_manager.so)

# add_custom_command(
#     TARGET r-type_client
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_audio_system>
#             ${LIB_SYSTEMS_DESTINATION}/r-type_audio_system.so)

# add_custom_command(
#     TARGET r-type_client
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_render_system>
#             ${LIB_SYSTEMS_DESTINATION}/r-type_render_system.so)

# add_custom_command(
#     TARGET r-type_client
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_collision_system>
#             ${LIB_SYSTEMS_DESTINATION}/r-type_collision_system.so)

