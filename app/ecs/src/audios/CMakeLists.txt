set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(r-type_sfml_audio SHARED
    SfmlAudio.cpp
)

target_include_directories(r-type_sfml_audio PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(
    r-type_sfml_audio
    r-type_interfaces
)
