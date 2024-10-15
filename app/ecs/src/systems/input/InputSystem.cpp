/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InputSystem
*/

#include <components/VelocityComponent.hpp>
#include <systems/InputSystem.hpp>

void ECS_system::InputSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities)
{
  for (auto &entity :
       _componentManager.getEntitiesWithComponents<component::InputComponent>(
           entities))
  {
    component::InputComponent *inputComponent = _componentManager.getComponent<component::InputComponent>(entity->getID());
    if (!inputComponent)
      return;

    sf::Vector2f newVelocity = {0, 0};
    if (inputComponent->isActionActive("MoveUp"))
      newVelocity.y = -200;
    if (inputComponent->isActionActive("MoveDown"))
      newVelocity.y = 200;
    if (inputComponent->isActionActive("MoveLeft"))
      newVelocity.x = -200;
    if (inputComponent->isActionActive("MoveRight"))
      newVelocity.x = 200;
    auto velocity = _componentManager.getComponent<component::VelocityComponent>(entity->getID());
    velocity->setVelocity(newVelocity);
    if (!inputComponent->isActionActive("Shoot"))
      return;

    component::WeaponComponent *weaponComponent = _componentManager.getComponent<component::WeaponComponent>(entity->getID());
    if (!weaponComponent)
      return;

    weaponComponent->setIsFiring(true);
  }
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager)
{
  return new ECS_system::InputSystem(componentManager, entityManager);
}