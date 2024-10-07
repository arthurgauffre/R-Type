/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SystemManager
*/

#include <managers/SystemManager.hpp>

/**
 * @brief Updates all systems managed by the SystemManager.
 *
 * This function iterates through all the systems and calls their update method,
 * passing the delta time to each system. Each system handles its own update
 * logic.
 *
 * @param deltaTime The time elapsed since the last update, used to update the
 * systems.
 */
void ECS_system::SystemManager::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) {
  for (auto &system : _systems) {
    system->update(deltaTime, entities); // Each system updates itself because
                                         // each system has its own logic
  }
}