/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SystemManager
*/

#pragma once

#pragma once

#include "ISystem.hpp"
#include <memory>
#include <vector>

namespace ECS_system {
class SystemManager {
public:
  /**
   * @brief Constructs a new SystemManager object.
   */
  SystemManager() = default;

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
  template <typename T, typename... Args> T *addSystem(Args &&...args) {
    auto system = std::make_unique<T>(std::forward<Args>(args)...);
    T *systemPtr = system.get();
    _systems.push_back(std::move(system));
    return systemPtr;
  }

  void update(float deltaTime,
              std::vector<std::shared_ptr<entity::IEntity>> entities);

private:
  /**
   * @brief A container holding unique pointers to ISystem objects.
   *
   * This vector manages the lifecycle of ISystem instances, ensuring that each
   * system is uniquely owned and properly destroyed when no longer needed.
   */
  std::vector<std::unique_ptr<ISystem>> _systems;
};
} // namespace ECS_system
