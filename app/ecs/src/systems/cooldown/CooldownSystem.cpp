/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CooldownSystem
*/

#include <systems/CooldownSystem.hpp>

#include <iostream>

/**
 * @brief Constructs a new CooldownSystem object.
 *
 * @param componentManager Reference to the ComponentManager.
 * @param entityManager Reference to the EntityManager.
 */
ECS_system::CooldownSystem::CooldownSystem(
    component::ComponentManager &componentManager,
    entity::EntityManager &entityManager)
    : ASystem(componentManager, entityManager) {}

/**
 * @brief Destructor for the CooldownSystem class.
 *
 * This destructor is responsible for cleaning up any resources
 * or performing any necessary finalization tasks when an instance
 * of the CooldownSystem class is destroyed.
 */
ECS_system::CooldownSystem::~CooldownSystem() {}

/**
 * @brief Updates the cooldown timers for entities with a CooldownComponent.
 *
 * This function iterates through all entities that have a CooldownComponent
 * and decreases their cooldown time by the given deltaTime. If the cooldown
 * time is greater than zero, it will be reduced by deltaTime.
 *
 * @param deltaTime The time elapsed since the last update.
 * @param entities A vector of shared pointers to entities to be updated.
 */
void ECS_system::CooldownSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) {
  for (auto &entity :
       _componentManager
           .getEntitiesWithComponents<component::CooldownComponent>(entities)) {
    component::CooldownComponent *cooldownComponent =
        _componentManager.getComponent<component::CooldownComponent>(
            entity.get()->getID());
    if (cooldownComponent->getTimeRemaining() > 0)
      cooldownComponent->setTimeRemaining(
          cooldownComponent->getTimeRemaining() - deltaTime);
  }
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager) {
  return new ECS_system::CooldownSystem(componentManager, entityManager);
}