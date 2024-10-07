/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreModule
*/

#ifndef COREMODULE_HPP_
#define COREMODULE_HPP_

#include <dlfcn.h>
#include <iostream>
#include <memory>
#include <r-type/ICoreModule.hpp>
#include <r-type/IModuleEngine.hpp>
#include <vector>

namespace rtype {
class CoreModule : virtual public ICoreModule {
public:
  CoreModule();
  ~CoreModule();

  // void setCoreStatus(CoreStatus status);
  // CoreStatus getCoreStatus() const;

  // rtype::IDisplayModule *getGraphicModule();
  // rtype::IGameModule *getGameModule();

  // void setGraphicModule(std::unique_ptr<rtype::IDisplayModule> module);
  // void setGameModule(std::unique_ptr<rtype::IGameModule> module);

  // void getLib(std::string pathLib);
  // void loadLib(std::string pathLib);
  // void addLibList(std::string pathLib);

  void loadEntityConstructor();
  void loadSystems();
  void loadComponents();
  void loadManagers();
  // void generateScore();

  // void handleKeyEvent(rtype::KeyboardInput key);
  // void launchSelection();
  // void addCharUsername(char c);
  // void handleKeySelection(rtype::KeyboardInput key);
  // void handleKeyRunning(rtype::KeyboardInput key);

  // rtype::ICoreModule::MenuData getMenuData() const;

  // void setGameData(rtype::GameData gameData);
  // rtype::GameData getGameData() const;

  // int coreLoop();
  // void runningLoop();
  // void updateRunning();
  // void selectionLoop();
  // void updateSelection();

  // void updateTimers();
  // void resetTimers(int index);
  // std::vector<rtype::timer> getTimers() const;
  // void setTimers(std::vector<rtype::timer> timers);

  template <typename T> class DLLoader {
  public:
    void *handle;

    // template <typename T>
    DLLoader(const std::string &libPath) {
      handle = dlopen(libPath.c_str(), RTLD_GLOBAL | RTLD_LAZY);
      if (!handle) {
        std::cerr << dlerror() << std::endl;
        exit(1);
      }
    };

    ~DLLoader(){};

    T getInstance(const std::string &funcName) {
      void *sym = dlsym(handle, funcName.c_str());
      if (!sym) {
        std::cerr << dlerror() << std::endl;
        exit(1);
      }
      return reinterpret_cast<T (*)()>(sym)();
    };

    void DLLunloader() {
      if (handle) {
        dlclose(handle);
      }
    };
  };
  std::vector<DLLoader<std::string>> _nameLoader;
  std::vector<DLLoader<rtype::ModuleType>> _libList;
  std::vector<DLLoader<std::shared_ptr<IModuleEngine>>> _interfaceList;
  // entity constructor
  std::shared_ptr<DLLoader<IEntity>> entityConstructor;

  // systems, managers and components loaders
  std::vector<DLLoader<std::shared_ptr<ISystem>>> _systems;
  std::vector<DLLoader<std::shared_ptr<IComponent>>> _components;
  std::vector<DLLoader<std::shared_ptr<IManager>>> _managers;
};
}; // namespace rtype

#endif /* !COREMODULE_HPP_ */