# Include the SFML package
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_library(r-type_server_system SHARED
    ServerSystem.cpp
    # ../../components/sprite/SpriteComponent.cpp
    # ../../components/texture/TextureComponent.cpp
    # ../../components/position/PositionComponent.cpp
    # ../../components/background/BackgroundComponent.cpp
    # ../../components/transform/TransformComponent.cpp
)

# Specify the SFML include directory
target_include_directories(r-type_server_system PRIVATE ${SFML_INCLUDE_DIR})

# Link the SFML library
target_link_libraries(
    r-type_server_system
    r-type_interfaces
    sfml-graphics
)
