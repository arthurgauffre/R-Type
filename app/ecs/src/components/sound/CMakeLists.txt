add_library(r-type_sound_component SHARED
    SoundComponent.cpp
)

# Specify the SFML include directory
target_include_directories(r-type_sound_component PRIVATE ${SFML_INCLUDE_DIR})

# Link the SFML library
target_link_libraries(
    r-type_sound_component
    r-type_interfaces
    sfml-audio
)
