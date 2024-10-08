/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ComponentManager
*/

#include <managers/ComponentManager.hpp>

component::ComponentManager::ComponentManager() {}

/**
 * @brief Updates all active components for each entity.
 *
 * This function iterates through all the components of each entity and calls
 * their update method if they are active. The update method is called with
 * the given delta time.
 *
 * @param deltaTime The time elapsed since the last update, used to update the
 * components.
 */
void component::ComponentManager::update(float deltaTime) {
  for (auto &entityComponents : _components) {
    for (auto &component : entityComponents.second) {
      if (component->getActive())
        component->update(deltaTime);
    }
  }
}

extern "C" std::shared_ptr<component::ComponentManager>
createComponentManager() {
  return std::make_shared<component::ComponentManager>();
}