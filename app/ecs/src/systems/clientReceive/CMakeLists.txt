add_library(r-type_client_receive_system SHARED
    ClientReceiveSystem.cpp
)

target_include_directories(r-type_client_receive_system PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(
    r-type_client_receive_system
    r-type_interfaces
    sfml-audio
)
