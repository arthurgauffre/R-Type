add_subdirectory(src/systems)
add_subdirectory(src/graphics)
add_subdirectory(src/audios)

set(LIB_DESTINATION ${CMAKE_SOURCE_DIR}/lib)
set(LIB_SYSTEMS_DESTINATION ${LIB_DESTINATION}/systems)
set(LIB_GRAPHICS_DESTINATION ${LIB_DESTINATION}/graphics)
set(LIB_AUDIOS_DESTINATION ${LIB_DESTINATION}/audios)

# Copy systems to lib/systems folder
add_custom_target(copy_systems ALL
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_audio_system>
            ${LIB_SYSTEMS_DESTINATION}/r-type_audio_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_render_system>
            ${LIB_SYSTEMS_DESTINATION}/r-type_render_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_collision_system>
            ${LIB_SYSTEMS_DESTINATION}/r-type_collision_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_input_system>
            ${LIB_SYSTEMS_DESTINATION}/r-type_input_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_movement_system>
            ${LIB_SYSTEMS_DESTINATION}/r-type_movement_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_health_system>
            ${LIB_SYSTEMS_DESTINATION}/r-type_health_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_weapon_system>
            ${LIB_SYSTEMS_DESTINATION}/r-type_weapon_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_client_system>
            ${LIB_SYSTEMS_DESTINATION}/r-type_client_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_server_system>
            ${LIB_SYSTEMS_DESTINATION}/r-type_server_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_cooldown_system>
            ${LIB_SYSTEMS_DESTINATION}/r-type_cooldown_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_ai_system>
            ${LIB_SYSTEMS_DESTINATION}/r-type_ai_system.so
    COMMAND $(CMAKE_COMMAND) -E copy $<TARGET_FILE:r-type_button_system>
            ${LIB_SYSTEMS_DESTINATION}/r-type_button_system.so)

# copy graphics to lib/graphics folder
add_custom_target(copy_graphics ALL
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_sfml_graphic>
            ${LIB_GRAPHICS_DESTINATION}/r-type_sfml_graphic.so)

# copy audios to lib/audios folder
add_custom_target(copy_audios ALL
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_sfml_audio>
            ${LIB_AUDIOS_DESTINATION}/r-type_sfml_audio.so)

add_dependencies(copy_systems r-type_audio_system r-type_render_system r-type_collision_system r-type_input_system r-type_movement_system r-type_health_system r-type_server_system r-type_cooldown_system r-type_weapon_system r-type_client_system r-type_ai_system r-type_button_system)
add_dependencies(copy_graphics r-type_sfml_graphic)
add_dependencies(copy_audios r-type_sfml_audio)