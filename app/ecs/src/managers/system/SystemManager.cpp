/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SystemManager
*/

#include <RtypeEngine.hpp>
#include <managers/SystemManager.hpp>

/**
 * @brief Constructs a new SystemManager object.
 *
 * This is the default constructor for the SystemManager class.
 * It initializes a new instance of the SystemManager.
 */
ECS_system::SystemManager::SystemManager() {}

/**
 * @brief Destructor for the SystemManager class.
 *
 * This destructor clears the _systems container, ensuring that all systems
 * managed by the SystemManager are properly cleaned up.
 */
ECS_system::SystemManager::~SystemManager() {
  _systems.clear();
}

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
    std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex) {
  for (auto &system : _systems) {
    system->update(deltaTime, entities,
                               msgToSend, msgReceived, entityMutex, _sceneStatus);
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
    entity::EntityManager &entityManager, std::string systemName, std::shared_ptr<IGraphic> graphic, StringCom stringCom) {
  std::shared_ptr<
      rtype::RtypeEngine::DLLoader<std::shared_ptr<ECS_system::ISystem>>>
      systemLoader = std::make_shared<
          rtype::RtypeEngine::DLLoader<std::shared_ptr<ECS_system::ISystem>>>(
          "lib/systems/r-type_" + systemName + "_system.so");

  if (!systemLoader) {
    std::cerr << "Error: systemLoader is null" << std::endl;
    exit(84);
  }

  std::shared_ptr<ECS_system::ISystem> system =
      std::shared_ptr<ECS_system::ISystem>(systemLoader->getSystem(
          "createSystem", componentManager, entityManager, graphic, stringCom));

  if (!system) {
    std::cerr << "Error: system is null" << std::endl;
    exit(84);
  }
  _systems.push_back(system);
}