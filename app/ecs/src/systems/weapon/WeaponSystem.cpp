/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WeaponSystem
*/

#include <systems/WeaponSystem.hpp>

ECS_system::WeaponSystem::WeaponSystem(
    component::ComponentManager &componentManager, entity::EntityManager &entityManager)
    : ASystem(componentManager, entityManager) {}

ECS_system::WeaponSystem::~WeaponSystem() {}

void ECS_system::WeaponSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) {}