/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** RtypeEngine
*/

#include <RtypeEngine.hpp>
#include <signal.h>
#include <atomic>
#include <iostream>

std::atomic<bool> keepRunning(true);

/**
 * @brief signal handler for SIGINT
 *
 * @param signum
 */
void signalHandler(int signum) {
    std::cout << "\nInterrupt signal (" << signum << ") received. Stopping...\n";
    keepRunning = false; // Set flag to false to stop the loop
}

/**
 * @brief Construct a new rtype::Core Module::Core Module object
 *
 */
rtype::RtypeEngine::RtypeEngine(std::string graphicName) {
  std::shared_ptr<
      rtype::RtypeEngine::DLLoader<std::shared_ptr<IGraphic>>>
      graphicLoader = std::make_shared<
          rtype::RtypeEngine::DLLoader<std::shared_ptr<IGraphic>>>(
          "lib/graphics/r-type_" + graphicName + "_graphic.so");
  if (!graphicLoader) {
    std::cerr << "Error: cannot load graphic library" << std::endl;
    exit(84);
  }
  this->_graphic = std::shared_ptr<IGraphic>(graphicLoader->getGraphic(
          "createGraphic"));
  this->_componentManager = std::make_shared<component::ComponentManager>();
  this->_systemManager = std::make_shared<ECS_system::SystemManager>();
  this->_entityManager = std::make_shared<entity::EntityManager>();
}

/**
 * @brief Destroy the rtype::Core Module::Core Module object
 *
 */
rtype::RtypeEngine::~RtypeEngine() {}

/**
 * @brief Retrieves the entity manager.
 *
 * This function returns a shared pointer to the EntityManager associated with
 * the RtypeEngine. The EntityManager is responsible for managing the entities
 * within the application.
 *
 * @return std::shared_ptr<entity::EntityManager> A shared pointer to the
 * EntityManager.
 */
std::shared_ptr<entity::EntityManager>
rtype::RtypeEngine::getEntityManager() const {
  return this->_entityManager;
}

/**
 * @brief Retrieves the component manager.
 *
 * This function returns a shared pointer to the component manager associated
 * with the RtypeEngine. The component manager is responsible for managing
 * various components within the module.
 *
 * @return std::shared_ptr<component::ComponentManager> Shared pointer to the
 * component manager.
 */
std::shared_ptr<component::ComponentManager>
rtype::RtypeEngine::getComponentManager() const {
  return this->_componentManager;
}

/**
 * @brief Retrieves the SystemManager instance.
 *
 * This function returns a shared pointer to the SystemManager instance
 * associated with the RtypeEngine. The SystemManager is responsible for
 * managing the various systems within the ECS (Entity Component System).
 *
 * @return std::shared_ptr<ECS_system::SystemManager> A shared pointer to the
 * SystemManager instance.
 */
std::shared_ptr<ECS_system::SystemManager>
rtype::RtypeEngine::getSystemManager() const {
  return this->_systemManager;
}

/**
 * @brief Runs the core module's main loop.
 *
 * This function starts a loop that continuously updates the system manager
 * with the elapsed time since the last update and the current entities from
 * the entity manager.
 */
void rtype::RtypeEngine::update() {
  float deltatime = clock.restart();
  _entityMutex.lock();
  auto entities = this->getEntityManager()->getEntities();
  _entityMutex.unlock();
  this->getSystemManager()->update(deltatime, entities, msgToSend, this->msgReceived, _entityMutex);
}

void rtype::RtypeEngine::run() {
  signal(SIGINT, signalHandler);
  while (1) {
    this->update();
    if (!keepRunning) {
      std::cout << "Exiting..." << std::endl;
      msgToSend.push_back(std::make_pair(Action::EXIT, 0));
      break;
    }
  }
  this->update();
}