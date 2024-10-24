/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InputSystem
*/

#include <components/VelocityComponent.hpp>
#include <systems/InputSystem.hpp>

void ECS_system::InputSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities,
    std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, size_t>> &msgReceived) {
  for (auto &entity :
       _componentManager.getEntitiesWithComponents<component::InputComponent>(
           entities)) {
    component::InputComponent *inputComponent =
        _componentManager.getComponent<component::InputComponent>(
            entity.get()->getID());
    if (inputComponent->isActionActive("MoveUp"))
      msgToSend.emplace_back("MoveUp", entity->getID());
    if (inputComponent->isActionActive("MoveDown"))
      msgToSend.emplace_back("MoveDown", entity->getID());
    if (inputComponent->isActionActive("MoveLeft"))
      msgToSend.emplace_back("MoveLeft", entity->getID());
    if (inputComponent->isActionActive("MoveRight"))
      msgToSend.emplace_back("MoveRight", entity->getID());
            entity->getID();
    if (!inputComponent)
      return;

    // component::WeaponComponent *weaponComponent =
    //     _componentManager.getComponent<component::WeaponComponent>(
    //         entity->getID());
    // if (!weaponComponent)
    //   return msgToSend;

    // weaponComponent->setIsFiring(true);
  }
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager) {
  return new ECS_system::InputSystem(componentManager, entityManager);
}