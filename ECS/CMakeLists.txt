# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name
project(RType)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(include/components)

set(SOURCES
    src/ComponentManager.cpp
    src/EntityManager.cpp
    main.cpp
)

add_executable(RType ${SOURCES})

set_target_properties(RType PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)