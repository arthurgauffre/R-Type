/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Isystem
*/

#include <r-type/IEntity.hpp>
#include <memory>
#include <vector>

namespace ECS_system {
class ISystem {
public:
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
         std::vector<std::shared_ptr<entity::IEntity>> entities) = 0;

  /**
   * @brief Pure virtual function to handle the components of the system.
   *
   * This function must be overridden by any derived class to define the
   * specific behavior for handling components within the system.
   */
  virtual void handleComponents() = 0;
};
} // namespace ECS_system
