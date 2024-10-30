/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ASystem
*/

#pragma once

#include <memory>
#include <r-type/ISystem.hpp>
#include <vector>
namespace ECS_system {
class ASystem : public ISystem {
public:
  /**
   * @class ASystem
   * @brief Abstract base class for systems in the ECS (Entity Component System)
   * architecture.
   *
   * @param componentManager Reference to the ComponentManager that manages all
   * components.
   */
  ASystem(component::ComponentManager &componentManager,
          entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic)
      : ISystem(componentManager, entityManager, graphic) {}

  /**
   * @brief Virtual destructor for the ASystem class.
   */
  virtual ~ASystem() = default;

  /**
   * @brief Pure virtual function to initialize the system.
   *
   * This function must be overridden by any derived class to provide
   * specific initialization logic for the system.
   */
  virtual void initialize() = 0;

  /**
   * @brief Updates the system with the given entities.
   *
   * This pure virtual function must be implemented by derived classes to update
   * the system's state based on the provided entities and the elapsed time.
   *
   * @param deltaTime The time elapsed since the last update, in seconds.
   * @param entities A vector of shared pointers to the entities to be updated.
   */
  virtual void
  update(float deltaTime,
         std::vector<std::shared_ptr<entity::IEntity>> entities,
         std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus) = 0;

  /**
   * @brief Pure virtual function to handle the components of the system.
   *
   * This function must be overridden by derived classes to define the specific
   * behavior for handling components within the system.
   */
  virtual void handleComponents() = 0;

protected:
  /**
   * @brief Reference to the ComponentManager instance.
   *
   * This member variable holds a reference to the ComponentManager, which is
   * responsible for managing all the components within the ECS (Entity
   * Component System). It provides functionalities to add, remove, and access
   * components associated with entities.
   */
};
} // namespace ECS_system
