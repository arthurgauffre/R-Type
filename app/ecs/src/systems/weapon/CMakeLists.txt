add_library(r-type_weapon_system SHARED
    WeaponSystem.cpp
    ../../components/damage/DamageComponent.cpp
    ../../components/parent/ParentComponent.cpp
)

# Specify the SFML include directory
target_include_directories(r-type_weapon_system PRIVATE ${SFML_INCLUDE_DIR})

# Link the SFML library
target_link_libraries(
    r-type_weapon_system
    r-type_interfaces
)
