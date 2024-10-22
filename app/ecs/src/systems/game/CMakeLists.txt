# Assuming this is at the beginning of your CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Include the SFML package
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# Add the shared library
add_library(r-type_game_system SHARED
    GameSystem.cpp
    ../../components/type/TypeComponent.cpp
)

# Set the include directories for SFML
target_include_directories(r-type_game_system PRIVATE ${SFML_INCLUDE_DIR})

# Link the interfaces library
target_link_libraries(
    r-type_game_system
    r-type_interfaces
)
