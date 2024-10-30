/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Isystem
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <r-type/Enum.hpp>
#include <managers/ComponentManager.hpp>
#include <managers/EntityManager.hpp>
#include <memory>
#include <r-type/IEntity.hpp>
#include <r-type/IGraphic.hpp>
#include <vector>
#include <mutex>

#ifdef _WIN32
#define EXPORT_API extern "C" __declspec(dllexport)
#else
#define EXPORT_API extern "C"
#endif

namespace ECS_system {
class ISystem {
public:
  ISystem(component::ComponentManager &componentManager,
          entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic)
      : _componentManager(componentManager), _entityManager(entityManager), _graphic(graphic) {}
  /*
  ** @brief Initializes the system.
  */
  virtual ~ISystem() = default;

  /**
   * @brief Pure virtual function to initialize the system.
   *
   * This function must be implemented by any derived class to perform
   * necessary initialization tasks for the system.
   */
  virtual void initialize() = 0;

  /**
   * @brief Updates the system with the given delta time and list of entities.
   *
   * This function is called to update the state of the system. It processes
   * the provided entities based on the elapsed time since the last update.
   *
   * @param deltaTime The time elapsed since the last update, in seconds.
   * @param entities A vector of shared pointers to the entities to be
   * processed.
   */
  virtual void
  update(float deltaTime,
         std::vector<std::shared_ptr<entity::IEntity>> entities,
         std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus) = 0;

  /**
   * @brief Pure virtual function to handle the components of the system.
   *
   * This function must be overridden by any derived class to define the
   * specific behavior for handling components within the system.
   */
  virtual void handleComponents() = 0;

protected:
  component::ComponentManager &_componentManager;
  entity::EntityManager &_entityManager;
  std::shared_ptr<IGraphic> _graphic;
};
} // namespace ECS_system
