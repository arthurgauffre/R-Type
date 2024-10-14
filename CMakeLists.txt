cmake_minimum_required(VERSION 3.10)

project(R-Type
    VERSION 0.1
    DESCRIPTION "R-Type game"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure Debug build type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the build type" FORCE)
endif()

if (WIN32)
    # Windows-specific settings
    # Set the vcpkg toolchain file first
    set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

    # Ensure SFML is installed through vcpkg if not found
    find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
    if (NOT SFML_FOUND)
        message(FATAL_ERROR "SFML not found! Make sure SFML is installed via vcpkg.")
    endif()

else()
    # Linux-specific settings (by adding a sanitizer)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif()

# Add the debug flag for GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb3")
endif()

# Find SFML via vcpkg
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Set the executable
add_executable(r-type_server
    app/server/main.cpp
)

add_executable(r-type_client
    app/client/main.cpp
    app/client/src/CoreModule.cpp
    app/ecs/src/managers/system/SystemManager.cpp
    app/ecs/src/managers/component/ComponentManager.cpp
    app/ecs/src/managers/entity/EntityManager.cpp
    app/ecs/src/components/sprite/SpriteComponent.cpp
    app/ecs/src/components/texture/TextureComponent.cpp
    app/ecs/src/components/position/PositionComponent.cpp
    app/ecs/src/components/hitbox/HitBoxComponent.cpp
    app/ecs/src/components/music/MusicComponent.cpp
    app/ecs/src/components/sound/SoundComponent.cpp
    app/ecs/src/components/input/InputComponent.cpp
    app/ecs/src/components/velocity/VelocityComponent.cpp
    app/ecs/src/components/transform/TransformComponent.cpp
    app/ecs/src/components/background/BackgroundComponent.cpp
    app/ecs/src/components/scroll/ScrollComponent.cpp
    app/ecs/src/entity/Entity.cpp
)

target_include_directories(r-type_client PRIVATE ${SFML_INCLUDE_DIR})

# Add the interface to the project
add_subdirectory(app/interface)
add_subdirectory(app/ecs)

# Link SFML and other libraries to the executables
target_link_libraries(r-type_server r-type_interfaces)
target_link_libraries(r-type_client r-type_interfaces sfml-graphics sfml-audio)

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

# Move .so/.dll files to the designated lib folder
set(LIB_DESTINATION ${CMAKE_SOURCE_DIR}/lib)
set(LIB_CLIENT_SYSTEMS_DESTINATION ${LIB_DESTINATION}/client_systems)
set(LIB_SERVER_SYSTEMS_DESTINATION ${LIB_DESTINATION}/server_systems)
set(LIB_SHARED_SYSTEMS_DESTINATION ${LIB_DESTINATION}/shared_systems)

# Additional custom commands to move shared system libraries
add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_audio_system>
            ${LIB_CLIENT_SYSTEMS_DESTINATION}/r-type_audio_system.so)

add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_render_system>
            ${LIB_CLIENT_SYSTEMS_DESTINATION}/r-type_render_system.so)

add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_collision_system>
            ${LIB_SERVER_SYSTEMS_DESTINATION}/r-type_collision_system.so)

add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_input_system>
            ${LIB_CLIENT_SYSTEMS_DESTINATION}/r-type_input_system.so)

add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_movement_system>
            ${LIB_CLIENT_SYSTEMS_DESTINATION}/r-type_movement_system.so)

add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_background_system>
            ${LIB_CLIENT_SYSTEMS_DESTINATION}/r-type_background_system.so)
