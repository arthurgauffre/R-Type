add_executable(r-type_server
    main.cpp
)

target_link_libraries(r-type_server r-type_interfaces r-type_server_interfaces)

add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_server> ${CMAKE_SOURCE_DIR}
)
