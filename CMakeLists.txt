cmake_minimum_required(VERSION 3.10)

project(R-Type
    VERSION 0.1
    DESCRIPTION "R-Type game"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug) # set build type to Debug

# Enable the sanitizer
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer"
)
set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fno-omit-frame-pointer"
)

# Add the debug flag
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb3")
endif()

# Add the executables for the project
add_executable(r-type_server
    app/server/main.cpp
)

add_executable(r-type_client
    app/client/main.cpp
)


# Move the executables to root of the project
add_custom_command(
    TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_server> ${CMAKE_SOURCE_DIR}
)

add_custom_command(
    TARGET r-type_client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_client> ${CMAKE_SOURCE_DIR}
)