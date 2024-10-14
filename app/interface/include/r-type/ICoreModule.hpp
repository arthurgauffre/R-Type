/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** ICoreModule
*/

#ifndef ICOREMODULE_HPP_
#define ICOREMODULE_HPP_

#ifdef _WIN32
#include <windows.h> // For Windows dynamic linking
#else
#include <dlfcn.h> // For POSIX dynamic linking
#endif

#include <SFML/Graphics.hpp>
#include <dirent.h>
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

  // enum CoreStatus
  // {
  //     RUNNING,
  //     SELECTION,
  //     EXIT
  // };
  // virtual void setCoreStatus(CoreStatus status) = 0;
  // virtual CoreStatus getCoreStatus() const = 0;

  // virtual rtype::IDisplayModule *getGraphicModule() = 0;
  // virtual rtype::IGameModule *getGameModule() = 0;

  // virtual void
  // setGraphicModule(std::unique_ptr<rtype::IDisplayModule> module) = 0;
  // virtual void setGameModule(std::unique_ptr<rtype::IGameModule> module) = 0;

  // virtual void getLib(std::string pathLib) = 0;
  // virtual void loadLib(std::string pathLib) = 0;
  // virtual void addLibList(std::string pathLib) = 0;

  // virtual void loadEntityConstructor() = 0;
  // virtual void loadSystems() = 0;
  // virtual void loadComponents() = 0;
  // virtual void loadManagers() = 0;

  // virtual std::vector<std::shared_ptr<ECS_system::ISystem>>
  // getSystems() const = 0;
  virtual std::shared_ptr<entity::EntityManager> getEntityManager() const = 0;
  virtual std::shared_ptr<component::ComponentManager>
  getComponentManager() const = 0;
  virtual std::shared_ptr<ECS_system::SystemManager>
  getSystemManager() const = 0;
  // virtual void generateScore() = 0;

  // virtual void handleKeyEvent(rtype::KeyboardInput key) = 0;
  // virtual void handleKeySelection(rtype::KeyboardInput key) = 0;
  // virtual void handleKeyRunning(rtype::KeyboardInput key) = 0;

  // MENU SELECTION
  // enum MenuSelection
  // {
  //     USERNAME,
  //     GAME,
  //     GRAPHIC
  // };
  // struct MenuData
  // {
  //     std::string _username;
  //     int indexGame;
  //     std::vector<std::string> _gameLibList;
  //     int indexGraphic;
  //     std::vector<std::string> _graphicLibList;
  //     std::string _description;
  //     MenuSelection _type;
  // };

  // virtual MenuData getMenuData() const = 0;

  // virtual void setGameData(rtype::GameData gameData) = 0;
  // virtual rtype::GameData getGameData() const = 0;

  // virtual int coreLoop() = 0;
  // virtual void runningLoop() = 0;
  // virtual void updateRunning() = 0;
  // virtual void selectionLoop() = 0;
  // virtual void updateSelection() = 0;

  // virtual void updateTimers() = 0;
  // virtual void resetTimers(int index) = 0;
  // virtual std::vector<timer> getTimers() const = 0;
  // virtual void setTimers(std::vector<rtype::timer> timers) = 0;

protected:
  // CoreStatus _coreStatus;
  // std::vector<timer> _timers;

  std::shared_ptr<entity::EntityManager> _entityManager;
  std::shared_ptr<component::ComponentManager> _componentManager;
  std::shared_ptr<ECS_system::SystemManager> _systemManager;
  // std::vector<std::shared_ptr<IManagers>> _managers;

  // rtype::IDisplayModule *_graphicModule;
  // rtype::IGameModule *_gameModule;
  // rtype::ICoreModule::MenuData _menuData;
  // rtype::GameData _gameData;

  // sf::RenderWindow *_window;
  // int _width;
  // int _height;
  // std::string _title;
  // float _deltaTime;
};
}; // namespace rtype

#endif /* !ICOREMODULE_HPP_ */