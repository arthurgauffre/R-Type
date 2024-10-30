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
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities,
    std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus) {
  // lock the entity mutex
  std::lock_guard<std::mutex> lock(entityMutex);
  for (auto &entity :
       _componentManager.getEntitiesWithComponents<component::InputComponent>(
           entities)) {
    if (entity->getSceneStatus() != *sceneStatus)
      continue;
    component::InputComponent *inputComponent =
        _componentManager.getComponent<component::InputComponent>(
            entity.get()->getID());

    for (auto &action : inputComponent->getKeyBindings()) {
      if (inputComponent->isActionActive(action.first)) {
        msgToSend.emplace_back(action.first, entity->getID());
      }
    }
    if (!inputComponent)
      return;
  }
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic) {
  return new ECS_system::InputSystem(componentManager, entityManager, graphic);
}