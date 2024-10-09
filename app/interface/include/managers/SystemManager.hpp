/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SystemManager
*/

#pragma once

#pragma once

#include <iostream>
#include <managers/ComponentManager.hpp>
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
  ~SystemManager() = default;

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
                 std::string systemName);

  void update(float deltaTime,
              std::vector<std::shared_ptr<entity::IEntity>> entities);

  std::vector<std::shared_ptr<ISystem>> getSystems() const { return _systems; }

  void hello() { std::cout << "Hello from SystemManager" << std::endl; }

private:
  /**
   * @brief A container holding unique pointers to ISystem objects.
   *
   * This vector manages the lifecycle of ISystem instances, ensuring that each
   * system is uniquely owned and properly destroyed when no longer needed.
   */
  std::vector<std::shared_ptr<ISystem>> _systems;
};
} // namespace ECS_system
