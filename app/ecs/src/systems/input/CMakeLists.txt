add_library(r-type_input_system SHARED
    InputSystem.cpp
    ../../components/input/InputComponent.cpp
)

# Specify the SFML include directory
target_include_directories(r-type_input_system PRIVATE ${SFML_INCLUDE_DIR})

# Link the SFML library
target_link_libraries(
    r-type_input_system
    r-type_interfaces
    sfml-graphics
)
