/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** ICoreModule
*/

#ifndef ICOREMODULE_HPP_
#define ICOREMODULE_HPP_

#ifdef _WIN32
#include <tchar.h>
#include <windows.h>
#else
#include <dirent.h>
#include <dlfcn.h> // For POSIX dynamic linking
#endif

#include <SFML/Graphics.hpp>
#include <iostream>
#include <managers/EntityManager.hpp>
#include <managers/SystemManager.hpp>
#include <r-type/IComponent.hpp>
#include <r-type/IEntity.hpp>

namespace rtype {
class ICoreModule {
public:
  ICoreModule(){};
  virtual ~ICoreModule(){};

  virtual std::shared_ptr<entity::EntityManager> getEntityManager() const = 0;
  virtual std::shared_ptr<component::ComponentManager>
  getComponentManager() const = 0;
  virtual std::shared_ptr<ECS_system::SystemManager>
  getSystemManager() const = 0;

protected:
  std::shared_ptr<entity::EntityManager> _entityManager;
  std::shared_ptr<component::ComponentManager> _componentManager;
  std::shared_ptr<ECS_system::SystemManager> _systemManager;
};
}; // namespace rtype

#endif /* !ICOREMODULE_HPP_ */