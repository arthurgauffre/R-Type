add_executable(r-type_client
    main.cpp
)

target_link_libraries(r-type_client r-type_interfaces r-type_client_interfaces)

add_custom_command(
    TARGET r-type_client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_client> ${CMAKE_SOURCE_DIR}
)

# Move .so files out of the build folder into the lib one
set(LIB_DESTINATION ${CMAKE_SOURCE_DIR}/lib)
set(LIB_COMPONENTS_DESTINATION ${LIB_DESTINATION}/components)
set(LIB_SYSTEMS_DESTINATION ${LIB_DESTINATION}/systems)
set(LIB_MANAGERS_DESTINATION ${LIB_DESTINATION}/managers)

add_custom_command(
  TARGET r-type_client
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_music_component>
          ${LIB_COMPONENTS_DESTINATION}/r-type_music_component.so)

add_custom_command(
  TARGET r-type_client
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_sound_component>
          ${LIB_COMPONENTS_DESTINATION}/r-type_sound_component.so)

add_custom_command(
  TARGET r-type_client
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_component_manager>
          ${LIB_MANAGERS_DESTINATION}/r-type_component_manager.so)

add_custom_command(
    TARGET r-type_client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_entity_manager>
            ${LIB_MANAGERS_DESTINATION}/r-type_entity_manager.so)

add_custom_command(
    TARGET r-type_client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_sprite_component>
            ${LIB_COMPONENTS_DESTINATION}/r-type_sprite_component.so)

add_custom_command(
    TARGET r-type_client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_texture_component>
            ${LIB_COMPONENTS_DESTINATION}/r-type_texture_component.so)

add_custom_command(
    TARGET r-type_client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_system_manager>
            ${LIB_MANAGERS_DESTINATION}/r-type_system_manager.so)

add_custom_command(
    TARGET r-type_client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_audio_system>
            ${LIB_SYSTEMS_DESTINATION}/r-type_audio_system.so)

add_custom_command(
    TARGET r-type_client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_render_system>
            ${LIB_SYSTEMS_DESTINATION}/r-type_render_system.so)

add_custom_command(
    TARGET r-type_client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_collision_system>
            ${LIB_SYSTEMS_DESTINATION}/r-type_collision_system.so)

