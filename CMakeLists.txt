cmake_minimum_required(VERSION 3.10)

project(R-Type
    VERSION 0.1
    DESCRIPTION "R-Type game"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug) # set build type to Debug

if (WIN32)
    # Windows-specific settings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    # Linux-specific settings (by adding a sanitizer)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lsfml-graphics -lsfml-audio")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif()

# Add the debug flag
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb3")
endif()

# Add the executables for the project
add_executable(r-type_server
    app/server/main.cpp
)

add_executable(r-type_client
    app/client/main.cpp
)

# Add the interface to the project
add_subdirectory(app/interface)
add_subdirectory(app/ecs)

# Link the interface to the executables
target_link_libraries(r-type_server r-type_interfaces)
target_link_libraries(r-type_client r-type_interfaces)

# Move the executables to root of the project
add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_server> ${CMAKE_SOURCE_DIR}
)

add_custom_command(
    TARGET r-type_client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_client> ${CMAKE_SOURCE_DIR}
)

# Move .so files out of the build folder into the lib one
set(LIB_DESTINATION ${CMAKE_SOURCE_DIR}/lib)

add_custom_command(
  TARGET r-type_server
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_music_component>
          ${LIB_DESTINATION}/r-type_music_component.so)

add_custom_command(
  TARGET r-type_server
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_sound_component>
          ${LIB_DESTINATION}/r-type_sound_component.so)

add_custom_command(
  TARGET r-type_server
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_component_manager>
          ${LIB_DESTINATION}/r-type_component_manager.so)

add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_entity_manager>
            ${LIB_DESTINATION}/r-type_entity_manager.so)

add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_sprite_component>
            ${LIB_DESTINATION}/r-type_sprite_component.so)

add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_texture_component>
            ${LIB_DESTINATION}/r-type_texture_component.so)

add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_system_manager>
            ${LIB_DESTINATION}/r-type_system_manager.so)

add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_audio_system>
            ${LIB_DESTINATION}/r-type_audio_system.so)

add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_render_system>
            ${LIB_DESTINATION}/r-type_render_system.so)

add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_collision_system>
            ${LIB_DESTINATION}/r-type_collision_system.so)
