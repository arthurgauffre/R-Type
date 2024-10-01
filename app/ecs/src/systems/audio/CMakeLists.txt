add_library(r-type_audio_system SHARED
    AudioSystem.cpp
)

target_link_libraries(
    r-type_audio_system
    r-type_interfaces
)
