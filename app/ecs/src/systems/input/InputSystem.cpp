/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InputSystem
*/

#include <systems/InputSystem.hpp>

void ECS_system::InputSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) {
  for (auto &entity :
       _componentManager.getEntitiesWithComponents<component::InputComponent>(
           entities)) {
    component::InputComponent *inputComponent =
        _componentManager.getComponent<component::InputComponent>(
            entity.get()->getID());
    if (inputComponent->isActionActive("MoveUp"))
      std::cout << "UP" << std::endl;
    else if (inputComponent->isActionActive("MoveDown"))
      std::cout << "DOWN" << std::endl;
    else if (inputComponent->isActionActive("MoveLeft"))
      std::cout << "LEFT" << std::endl;
    else if (inputComponent->isActionActive("MoveRight"))
      std::cout << "RIGHT" << std::endl;
    else
      std::cout << "IDLE" << std::endl;
  }
}

extern "C" std::shared_ptr<ECS_system::ISystem>
createInputSystem(component::ComponentManager &componentManager) {
  return std::make_shared<ECS_system::InputSystem>(componentManager);
}