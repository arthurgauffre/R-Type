add_library(r-type_background_system SHARED
    BackgroundSystem.cpp
    ../../components/background/BackgroundComponent.cpp
    ../../components/scroll/ScrollComponent.cpp
    ../../components/position/PositionComponent.cpp
)

target_include_directories(r-type_background_system PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(
    r-type_background_system
    r-type_interfaces
    sfml-graphics
)
