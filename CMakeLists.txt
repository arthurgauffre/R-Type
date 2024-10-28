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
    # Set the vcpkg toolchain file first
    set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
    # Add the install of the SFML library
    execute_process(COMMAND vcpkg integrate install)
    execute_process(COMMAND vcpkg install sfml)
endif()

if (UNIX)
    # Detect the current Linux distribution using /etc/os-release
    execute_process(
        COMMAND uname -s
        OUTPUT_VARIABLE OS_NAME
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # Reading the /etc/os-release file to get the ID of the distribution
    file(READ /etc/os-release OS_RELEASE_CONTENTS)

    string(REGEX MATCH "ID=([^\n]+)" _ ${OS_RELEASE_CONTENTS})
    set(DISTRO ${CMAKE_MATCH_1})

    # Set the package manager based on the detected distribution
    if(DISTRO STREQUAL "fedora" OR DISTRO STREQUAL "rhel" OR DISTRO STREQUAL "centos")
        set(PACKAGE_MANAGER "dnf install")
    elseif(DISTRO STREQUAL "ubuntu" OR DISTRO STREQUAL "debian" OR DISTRO STREQUAL "linuxmint")
        set(PACKAGE_MANAGER "apt-get install")
    elseif(DISTRO STREQUAL "arch" OR DISTRO STREQUAL "manjaro")
        set(PACKAGE_MANAGER "pacman -S")
    elseif(DISTRO STREQUAL "opensuse")
        set(PACKAGE_MANAGER "zypper install")
    else()
        message(WARNING "Unknown Linux distribution: ${DISTRO}")
        set(PACKAGE_MANAGER "unknown")
    endif()

    # Output the detected package manager
    message(STATUS "Detected Linux distribution: ${DISTRO}")

    # Add the install of the SFML library
    if (NOT EXISTS "/usr/include/SFML")
        execute_process(COMMAND sudo ${PACKAGE_MANAGER} libsfml-dev)
    endif()
    # Linux-specific settings (by adding a sanitizer)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif()

# Add the debug flag for GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb3")
endif()

# Find SFML using vcpkg
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

if(SFML_FOUND)
    message(STATUS "SFML found: ${SFML_DIR}")
else()
    message(FATAL_ERROR "SFML not found")
endif()

# Add the executables for the project



include_directories(${CMAKE_SOURCE_DIR}/3rd_party_lib/asio/asio/include)


# Add the interface to the project
add_subdirectory(interface)
add_subdirectory(app/ecs)
add_subdirectory(app/server)
add_subdirectory(app/client)


# Link the interface to the executables
# target_link_libraries(r-type_client r-type_interfaces)

# Move the executables to root of the project


