add_subdirectory(src/systems)

set(LIB_DESTINATION ${CMAKE_SOURCE_DIR}/lib)
set(LIB_CLIENT_SYSTEMS_DESTINATION ${LIB_DESTINATION}/client_systems)
set(LIB_SERVER_SYSTEMS_DESTINATION ${LIB_DESTINATION}/server_systems)
set(LIB_SHARED_SYSTEMS_DESTINATION ${LIB_DESTINATION}/shared_systems)

# Copy shared object files to the designated directories
add_custom_target(copy_systems ALL
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_audio_system>
            ${LIB_CLIENT_SYSTEMS_DESTINATION}/r-type_audio_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_render_system>
            ${LIB_CLIENT_SYSTEMS_DESTINATION}/r-type_render_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_collision_system>
            ${LIB_CLIENT_SYSTEMS_DESTINATION}/r-type_collision_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_input_system>
            ${LIB_CLIENT_SYSTEMS_DESTINATION}/r-type_input_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_movement_system>
            ${LIB_CLIENT_SYSTEMS_DESTINATION}/r-type_movement_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_health_system>
            ${LIB_CLIENT_SYSTEMS_DESTINATION}/r-type_health_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_weapon_system>
            ${LIB_CLIENT_SYSTEMS_DESTINATION}/r-type_weapon_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_client_system>
            ${LIB_CLIENT_SYSTEMS_DESTINATION}/r-type_client_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_server_system>
            ${LIB_CLIENT_SYSTEMS_DESTINATION}/r-type_server_system.so
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_cooldown_system>
            ${LIB_CLIENT_SYSTEMS_DESTINATION}/r-type_cooldown_system.so
)

add_dependencies(copy_systems r-type_audio_system r-type_render_system r-type_collision_system r-type_input_system r-type_movement_system r-type_health_system r-type_server_system r-type_cooldown_system r-type_weapon_system r-type_client_system)
