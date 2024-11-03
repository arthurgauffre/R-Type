/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SystemManager
*/

#pragma once
#include <iostream>
#include <managers/ComponentManager.hpp>
#include <managers/EntityManager.hpp>
#include <memory>
#include <r-type/ISystem.hpp>
#include <vector>

namespace ECS_system {
class SystemManager {
public:
  /**
   * @brief Constructs a new SystemManager object.
   */
  SystemManager();

  /**
   * @brief Destroys the SystemManager object.
   */
  ~SystemManager();

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
  void addSystem(component::ComponentManager &componentManager,
                 entity::EntityManager &entityManager, std::string systemName, std::shared_ptr<IGraphic> graphic, std::shared_ptr<IAudio> audio, StringCom stringCom);

  /**
   * @brief Updates the system manager.
   *
   * @param deltaTime The time elapsed since the last update.
   * @param entities A vector of shared pointers to entities to be updated.
   * @param msgToSend A reference to a vector of pairs containing actions and their corresponding entity IDs to be sent.
   * @param msgReceived A reference to a vector of pairs containing messages and their corresponding sender and receiver IDs.
   * @param entityMutex A reference to a mutex for synchronizing access to entities.
   */
  void
  update(float deltaTime,
         std::vector<std::shared_ptr<entity::IEntity>> entities,
         std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex);

  /**
   * @brief Retrieves the list of systems managed by the SystemManager.
   *
   * @return A vector of shared pointers to ISystem objects.
   */
  std::vector<std::shared_ptr<ISystem>> getSystems() const { return _systems; }

private:
  /**
   * @brief A container holding unique pointers to ISystem objects.
   *
   * This vector manages the lifecycle of ISystem instances, ensuring that each
   * system is uniquely owned and properly destroyed when no longer needed.
   */
  std::vector<std::shared_ptr<ISystem>> _systems;

  /**
   * @brief A shared pointer to a Scene object.
   *
   * This shared pointer manages the lifetime of a Scene object, ensuring that
   * the object is properly deleted when no more shared pointers point to it.
   * The Scene object is initialized with the Scene::MENU state.
   */
  std::shared_ptr<Scene> _sceneStatus = std::make_shared<Scene>(Scene::MENU);

};
} // namespace ECS_system
