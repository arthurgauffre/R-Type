# Include subdirectories

# add_library(a_display_module STATIC
#     ADisplayModule.cpp
# )

# set_target_properties(a_display_module PROPERTIES
#     POSITION_INDEPENDENT_CODE ON
# )

# target_link_libraries(a_display_module
#     arcade_interfaces
# )

#add_library(graphics STATIC ADisplayModule.cpp ADisplayModule.hpp)

# Create a shared library for graphics
# add_custom_target(graphics_module DEPENDS Sdl2 NCurses Sfml)
#add_library(graphics SHARED "")
#target_link_libraries(graphics Sdl2 NCurses Sfml)

add_subdirectory(audio)
add_subdirectory(collision)
add_subdirectory(render)
