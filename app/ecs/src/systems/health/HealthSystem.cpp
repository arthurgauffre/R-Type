/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HealthSystem
*/

#include <systems/HealthSystem.hpp>

/**
 * @brief Constructs a new HealthSystem object.
 *
 * This constructor initializes the HealthSystem by invoking the base class
 * constructor with the provided ComponentManager reference.
 *
 * @param componentManager Reference to the ComponentManager that manages
 * the components associated with this system.
 */
ECS_system::HealthSystem::HealthSystem(
    component::ComponentManager &componentManager,
    entity::EntityManager &entityManager)
    : ASystem(componentManager, entityManager) {}

/**
 * @brief Destructor for the HealthSystem class.
 *
 * This destructor is responsible for cleaning up any resources
 * or performing any necessary finalization tasks when an instance
 * of the HealthSystem class is destroyed.
 */
ECS_system::HealthSystem::~HealthSystem() {}

#include <iostream>

/**
 * @brief Updates the health status of entities and deactivates those with zero
 * or negative health.
 *
 * This function iterates through a list of entities, checks their health
 * status, and deactivates any entity whose health is less than or equal to
 * zero.
 *
 * @param deltaTime The time elapsed since the last update.
 * @param entities A vector of shared pointers to entities that need to be
 * updated.
 */
void ECS_system::HealthSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities,
    std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, size_t>> &msgReceived) {
  for (auto &entity :
       _componentManager.getEntitiesWithComponents<component::HealthComponent>(
           entities)) {
    component::HealthComponent *healthComponent =
        _componentManager.getComponent<component::HealthComponent>(
            entity->getID());
    healthComponent->setHealth(healthComponent->getHealth() -
                               healthComponent->getDamageIncoming());
    healthComponent->setDamageIncoming(0);
    if (healthComponent->getHealth() <= 0) {
      _entityManager.destroyEntity(entity->getID());
    }
  }
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager) {
  return new ECS_system::HealthSystem(componentManager, entityManager);
}