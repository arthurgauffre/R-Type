/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InputSystem
*/

#include <components/VelocityComponent.hpp>
#include <systems/InputSystem.hpp>

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
          -velocityComponent->getVelocity().y);
    if (inputComponent->isActionActive("MoveDown"))
      velocityComponent->setActualVelocityY(velocityComponent->getVelocity().y);
    if (inputComponent->isActionActive("MoveLeft"))
      velocityComponent->setActualVelocityX(
          -velocityComponent->getVelocity().x);
    if (inputComponent->isActionActive("MoveRight"))
      velocityComponent->setActualVelocityX(velocityComponent->getVelocity().x);
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