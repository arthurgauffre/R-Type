set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(r-type_audio_system SHARED
    AudioSystem.cpp
    ../../components/music/MusicComponent.cpp
    ../../components/sound/SoundComponent.cpp
    ../../managers/component/ComponentManager.cpp
)

target_link_libraries(
    r-type_audio_system
    r-type_interfaces
    sfml-audio
)
