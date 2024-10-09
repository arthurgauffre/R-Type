add_library(r-type_system_manager SHARED
    SystemManager.cpp
    ../../managers/component/ComponentManager.cpp
)

target_link_libraries(
    r-type_system_manager
    r-type_interfaces
)
