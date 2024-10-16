/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InputSystem
*/

#include <components/VelocityComponent.hpp>
#include <systems/InputSystem.hpp>

std::vector<std::string> ECS_system::InputSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities,
    std::vector<std::string> msgToSend) {
  for (auto &entity :
       _componentManager.getEntitiesWithComponents<component::InputComponent>(
           entities)) {
    component::InputComponent *inputComponent =
        _componentManager.getComponent<component::InputComponent>(
            entity.get()->getID());
    sf::Vector2f newVelocity = {0, 0};
    if (inputComponent->isActionActive("MoveUp"))
      msgToSend.push_back("MoveUp");
    if (inputComponent->isActionActive("MoveDown"))
      msgToSend.push_back("MoveDown");
    if (inputComponent->isActionActive("MoveLeft"))
      msgToSend.push_back("MoveLeft");
    if (inputComponent->isActionActive("MoveRight"))
      msgToSend.push_back("MoveRight");
  }
  return msgToSend;
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager) {
  return new ECS_system::InputSystem(componentManager, entityManager);
}