/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CooldownSystem
*/

#include <systems/CooldownSystem.hpp>

#include <iostream>

ECS_system::CooldownSystem::CooldownSystem(
    component::ComponentManager &componentManager,
    entity::EntityManager &entityManager)
    : ASystem(componentManager, entityManager) {}

ECS_system::CooldownSystem::~CooldownSystem() {}

void ECS_system::CooldownSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities)
{
    for (auto &entity : _componentManager.getEntitiesWithComponents<component::CooldownComponent>(entities))
    {
        component::CooldownComponent *cooldownComponent = _componentManager.getComponent<component::CooldownComponent>(entity.get()->getID());
        if (cooldownComponent->getTimeRemaining() > 0)
            cooldownComponent->setTimeRemaining(cooldownComponent->getTimeRemaining() - deltaTime);
    }
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager)
{
    return new ECS_system::CooldownSystem(componentManager, entityManager);
}