add_library(r-type_entity_manager SHARED
    EntityManager.cpp
    ../../entity/Entity.cpp
    ../../managers/component/ComponentManager.cpp
)

target_link_libraries(
    r-type_entity_manager
    r-type_interfaces
)
