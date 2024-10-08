add_library(r-type_entity SHARED
    Entity.cpp
)

target_link_libraries(
    r-type_entity
    r-type_interfaces
)
