/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SystemManager
*/

#include <CoreModule.hpp>
#include <managers/SystemManager.hpp>

ECS_system::SystemManager::SystemManager() {}

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
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities,
    std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, size_t>> &msgReceived, std::mutex &entityMutex) {
  for (auto &system : _systems) {
    system->update(deltaTime, entities,
                               msgToSend, msgReceived, entityMutex); // Each system updates itself because
                                           // each system has its own logic
  }
}

/**
 * @brief Adds a new system to the manager.
 *
 * This function creates a new system of type T with the provided arguments,
 * stores it in the manager, and returns a pointer to the created system.
 *
 * @tparam T The type of the system to be added.
 * @tparam Args The types of the arguments to be forwarded to the system's
 * constructor.
 * @param args The arguments to be forwarded to the system's constructor.
 * @return T* A pointer to the newly created system.
 */
void ECS_system::SystemManager::addSystem(
    component::ComponentManager &componentManager,
    entity::EntityManager &entityManager, std::string systemName) {
  std::shared_ptr<
      rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>
      systemLoader = std::make_shared<
          rtype::CoreModule::DLLoader<std::shared_ptr<ECS_system::ISystem>>>(
          "lib/client_systems/r-type_" + systemName + "_system.so");

  // check if the systemLoader is not null
  if (!systemLoader) {
    std::cerr << "Error: systemLoader is null" << std::endl;
    exit(84);
  }

  // Wrap the returned raw pointer in a shared_ptr
  std::shared_ptr<ECS_system::ISystem> system =
      std::shared_ptr<ECS_system::ISystem>(systemLoader->getInstance(
          "createSystem", componentManager, entityManager));

  // check if the system is not null
  if (!system) {
    std::cerr << "Error: system is null" << std::endl;
    exit(84);
  }
  // Add to the systems manager
  _systems.push_back(system);
}