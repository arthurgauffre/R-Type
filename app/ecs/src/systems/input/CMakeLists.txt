set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(r-type_input_system SHARED
    InputSystem.cpp
    ../../components/input/InputComponent.cpp
    ../../components/weapon/WeaponComponent.cpp
)

target_include_directories(r-type_input_system PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(
    r-type_input_system
    r-type_interfaces
    sfml-graphics
)
