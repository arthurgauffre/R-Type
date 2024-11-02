/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IRtypeEngine
*/

#ifndef ICOREMODULE_HPP_
#define ICOREMODULE_HPP_

#pragma once
#include <SFML/Graphics.hpp>

#ifdef _WIN32
#include <tchar.h>
#include <windows.h>
#else
#include <dirent.h>
#include <dlfcn.h>
#include <unistd.h>
#endif

#include <iostream>
#include <managers/EntityManager.hpp>
#include <managers/SystemManager.hpp>
#include <r-type/IComponent.hpp>
#include <r-type/IEntity.hpp>

namespace rtype {
class IRtypeEngine {
public:
  /**
   * @class IRtypeEngine
   * @brief Interface for the R-Type game engine.
   *
   * This class provides the interface for the R-Type game engine.
   * It defines the necessary methods and properties that any R-Type
   * game engine implementation should have.
   */
  IRtypeEngine(){};

  /**
   * @brief Virtual destructor for the IRtypeEngine interface.
   *
   * This destructor ensures that derived classes can clean up resources properly
   * when an object of IRtypeEngine or its derived class is deleted.
   */
  virtual ~IRtypeEngine(){};

  /**
   * @brief Retrieve the EntityManager instance.
   *
   * This function returns a shared pointer to the EntityManager, which is responsible
   * for managing all entities within the engine. The EntityManager handles the creation,
   * deletion, and updating of entities.
   *
   * @return std::shared_ptr<entity::EntityManager> A shared pointer to the EntityManager.
   */
  virtual std::shared_ptr<entity::EntityManager> getEntityManager() const = 0;

  /**
   * @brief Retrieves the component manager.
   *
   * This function returns a shared pointer to the component manager, which is responsible
   * for managing the various components within the engine.
   *
   * @return std::shared_ptr<component::ComponentManager> A shared pointer to the component manager.
   */
  virtual std::shared_ptr<component::ComponentManager> getComponentManager() const = 0;

  /**
   * @brief Retrieves the SystemManager instance.
   *
   * This function returns a shared pointer to the SystemManager, which is responsible
   * for managing the various systems within the ECS (Entity Component System).
   *
   * @return std::shared_ptr<ECS_system::SystemManager> A shared pointer to the SystemManager.
   */
  virtual std::shared_ptr<ECS_system::SystemManager> getSystemManager() const = 0;

  /**
   * @brief Pure virtual function to update the state of the engine.
   *
   * This function should be overridden by derived classes to implement
   * the specific update logic for the engine. It is called to perform
   * any necessary updates to the engine's state.
   */
  virtual void update() = 0;

  /**
   * @brief Pure virtual function to run the engine.
   *
   * This function must be implemented by any derived class to define the
   * specific behavior of the engine when it is run.
   */
  virtual void run() = 0;

protected:
  /**
   * @brief A shared pointer to an EntityManager instance.
   *
   * This member variable holds a shared pointer to an EntityManager, which is responsible
   * for managing the lifecycle and interactions of entities within the R-Type engine.
   * Using a shared pointer ensures that the EntityManager instance is properly managed
   * and deallocated when no longer in use, preventing memory leaks.
   */
  std::shared_ptr<entity::EntityManager> _entityManager;

  /**
   * @brief A shared pointer to the ComponentManager.
   *
   * This member variable holds a shared pointer to an instance of the
   * ComponentManager, which is responsible for managing the components
   * within the R-Type engine. The use of a shared pointer ensures that
   * the ComponentManager instance is properly managed and its lifetime
   * is controlled, preventing memory leaks and dangling pointers.
   */
  std::shared_ptr<component::ComponentManager> _componentManager;

  /**
   * @brief A shared pointer to the SystemManager instance.
   *
   * This member variable holds a shared pointer to an instance of the
   * SystemManager class from the ECS_system namespace. The SystemManager
   * is responsible for managing the various systems within the ECS (Entity
   * Component System) architecture.
   */
  std::shared_ptr<ECS_system::SystemManager> _systemManager;
};
}; // namespace rtype

#endif /* !ICOREMODULE_HPP_ */