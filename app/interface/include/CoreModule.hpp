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

  std::vector<std::shared_ptr<ECS_system::ISystem>> getSystems() const;

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

    DLLoader(const std::string &libPath) {
      handle = dlopen(libPath.c_str(), RTLD_GLOBAL | RTLD_LAZY);
      if (!handle) {
        std::cerr << dlerror() << std::endl;
        exit(1);
      }
    }

    ~DLLoader() {}

    // Remove the extra qualification "DLLoader<T>::"
    template <typename... Args>
    std::shared_ptr<T> getInstance(const std::string &funcName, Args... args) {
      using FuncPtr = std::shared_ptr<T> (*)(
          Args...); // Define the function pointer type returning shared_ptr
      void *sym = dlsym(handle, funcName.c_str());
      if (!sym) {
        std::cerr << dlerror() << std::endl;
        exit(1);
      }
      FuncPtr createFunc = reinterpret_cast<FuncPtr>(
          sym);                   // Cast to the correct function pointer type
      return createFunc(args...); // Call the function and return the shared_ptr
    }

    void DLLunloader() {
      if (handle) {
        dlclose(handle);
      }
    };
  };

  // entity constructor
  std::shared_ptr<DLLoader<entity::IEntity>> entityConstructor;

  // undored map of components constructors
  std::unordered_map<std::string,
                     std::shared_ptr<DLLoader<component::IComponent>>>
      _components;

  // std::vector<DLLoader<std::shared_ptr<ECS_system::ISystem>>> _systems;
  // std::vector<DLLoader<std::shared_ptr<component::IComponent>>> _components;
  // std::vector<DLLoader<std::shared_ptr<IManager>>> _managers;

  std::vector<DLLoader<std::string>> _nameLoader;
  // std::vector<DLLoader<rtype::ModuleType>> _libList;
  // std::vector<DLLoader<std::shared_ptr<IModuleEngine>>> _interfaceList;
  // entity constructor
};
}; // namespace rtype

#endif /* !COREMODULE_HPP_ */