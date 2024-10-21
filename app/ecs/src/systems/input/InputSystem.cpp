/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InputSystem
*/

#include <components/VelocityComponent.hpp>
#include <systems/InputSystem.hpp>

/**
 * @brief Updates the input system for all entities with input components.
 *
 * This function processes input actions for entities and updates their
 * velocity and firing state based on the input received. It iterates through
 * all entities that have an InputComponent and performs the following actions:
 * - Resets the entity's velocity to zero.
 * - Updates the entity's velocity based on active input actions ("MoveUp",
 *   "MoveDown", "MoveLeft", "MoveRight").
 * - Sets the entity's firing state if the "Shoot" action is active.
 *
 * @param deltaTime The time elapsed since the last update.
 * @param entities A vector of shared pointers to entities to be updated.
 */
void ECS_system::InputSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) {
  for (auto &entity :
       _componentManager.getEntitiesWithComponents<component::InputComponent>(
           entities)) {
    component::InputComponent *inputComponent =
        _componentManager.getComponent<component::InputComponent>(
            entity->getID());
    if (!inputComponent)
      return;
    component::VelocityComponent *velocityComponent =
        _componentManager.getComponent<component::VelocityComponent>(
            entity->getID());
    velocityComponent->setActualVelocityX(0);
    velocityComponent->setActualVelocityY(0);
    if (inputComponent->isActionActive("MoveUp"))
      velocityComponent->setActualVelocityY(
          -velocityComponent->getVelocity().second);
    if (inputComponent->isActionActive("MoveDown"))
      velocityComponent->setActualVelocityY(
          velocityComponent->getVelocity().second);
    if (inputComponent->isActionActive("MoveLeft"))
      velocityComponent->setActualVelocityX(
          -velocityComponent->getVelocity().first);
    if (inputComponent->isActionActive("MoveRight"))
      velocityComponent->setActualVelocityX(
          velocityComponent->getVelocity().first);
    if (!inputComponent->isActionActive("Shoot"))
      return;

    component::WeaponComponent *weaponComponent =
        _componentManager.getComponent<component::WeaponComponent>(
            entity->getID());
    if (!weaponComponent)
      return;

    weaponComponent->setIsFiring(true);
  }
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager) {
  return new ECS_system::InputSystem(componentManager, entityManager);
}