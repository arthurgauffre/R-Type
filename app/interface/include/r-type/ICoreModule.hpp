/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** ICoreModule
*/

#ifndef ICOREMODULE_HPP_
#define ICOREMODULE_HPP_

#include <dirent.h>
#include <iostream>
#include <r-type/IComponent.hpp>
#include <r-type/IEntity.hpp>
#include <r-type/IManager.hpp>
#include <r-type/ISystem.hpp>

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

  virtual void loadEntityConstructor() = 0;
  // virtual void loadSystems() = 0;
  // virtual void loadComponents() = 0;
  // virtual void loadManagers() = 0;
  virtual void helloWorld() = 0;
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

  std::vector<std::shared_ptr<entity::IEntity>> _entities;
  // std::vector<std::shared_ptr<ISystem>> _systems;
  // std::vector<std::shared_ptr<IComponent>> _components;
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

  // entity::EntityManager _entityManager;
  // component::ComponentManager _componentManager;
  // ECS_system::SystemManager _systemManager;
};
}; // namespace rtype

#endif /* !ICOREMODULE_HPP_ */