add_library(r-type_position_component SHARED
    PositionComponent.cpp
)

target_link_libraries(
    r-type_position_component
    r-type_interfaces
)
