cmake_minimum_required(VERSION 3.10)

project(R-Type
    VERSION 0.1
    DESCRIPTION "R-Type game"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug) # set build type to Debug

if (WIN32)
    # Windows-specific settings
  execute_process(COMMAND vcpkg integrate install)
  execute_process(COMMAND vcpkg install sfml)
else()
    # Linux-specific settings (by adding a sanitizer)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lsfml-graphics -lsfml-audio")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif()

# Add the debug flag
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb3")
endif()

# find_package(SFML 2.5 COMPONENTS audio graphics REQUIRED)

# Set SFML include directories
# set(SFML_INCLUDE_DIR ${SFML_DIR}/include)

# if(SFML_FOUND)
#     message(STATUS "SFML found: ${SFML_DIR}")
# else()
#     message(FATAL_ERROR "SFML not found")
# endif()

# Add the executables for the project




# Add the interface to the project
add_subdirectory(interface)
add_subdirectory(app/ecs)
add_subdirectory(app/server)
add_subdirectory(app/client)

# Link the interface to the executables
# target_link_libraries(r-type_client r-type_interfaces)

# Move the executables to root of the project



