/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** RtypeEngine
*/

#ifndef COREMODULE_HPP_
#define COREMODULE_HPP_

#pragma once
#include <iostream>
#include <limits.h>
#include <memory>
#include <r-type/Entity.hpp>
#include <r-type/IRtypeEngine.hpp>
#include <r-type/ISystem.hpp>
#include <vector>

#include <components/DamageComponent.hpp>
#include <components/HealthComponent.hpp>
#include <components/HitBoxComponent.hpp>
#include <components/InputComponent.hpp>
#include <components/MusicComponent.hpp>
#include <components/ParentComponent.hpp>
#include <components/SizeComponent.hpp>
#include <components/SoundComponent.hpp>
#include <components/SpriteComponent.hpp>
#include <components/TextureComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/TypeComponent.hpp>
#include <components/VelocityComponent.hpp>
#include <components/WeaponComponent.hpp>
#include <components/CooldownComponent.hpp>
#include <components/SizeComponent.hpp>
#include <components/AIComponent.hpp>

#include <r-type/IGraphic.hpp>

namespace rtype {
class RtypeEngine : virtual public IRtypeEngine {
public:
  RtypeEngine(std::string graphicName);
  ~RtypeEngine();

  entity::IEntity *createBackground(std::string texturePath,
                                    std::pair<float, float> speed,
                                    std::pair<float, float> size);
  entity::IEntity *createPlayer(uint32_t entityID, std::string texturePath,
                                std::pair<float, float> position,
                                std::pair<float, float> velocity,
                                std::pair<float, float> scale, int health);
  entity::IEntity *createEnemy(uint32_t entityID, std::string texturePath,
                               std::pair<float, float> position,
                               std::pair<float, float> velocity,
                               std::pair<float, float> scale, int health,
                               int damage);
  entity::IEntity *createWeapon(uint32_t parentID, std::string type, int damage,
                                float cooldown);

  void update();
  void run();

  std::shared_ptr<entity::EntityManager> getEntityManager() const;
  std::shared_ptr<component::ComponentManager> getComponentManager() const;
  std::shared_ptr<ECS_system::SystemManager> getSystemManager() const;

  std::vector<std::pair<std::string, std::pair<size_t, size_t>>> msgReceived;
  std::vector<std::pair<std::string, size_t>> msgToSend;
  sf::Clock clock;
  std::mutex _entityMutex;
  std::shared_ptr<IGraphic> _graphic;

  template <typename T> class DLLoader {
  public:
    void *handle;

    DLLoader(const std::string &libPath) {
#ifdef _WIN32
      handle = LoadLibrary(libPath.c_str());
      if (!handle) {
        std::cerr << "Error loading library: " << libPath
                  << " Error: " << GetLastError() << std::endl;
        exit(1);
      }
#else
      handle = dlopen(libPath.c_str(), RTLD_GLOBAL | RTLD_LAZY);
      if (!handle) {
        std::cerr << dlerror() << std::endl;
        exit(1);
      }
#endif
    }

    ~DLLoader() {}
    template <typename... Args>
    ECS_system::ISystem *getSystem(const std::string &funcName,
                                     Args &&...args) {
      using FuncPtr =
          ECS_system::ISystem *(*)(Args...); // Function pointer type
      void *sym;

#ifdef _WIN32
      sym = GetProcAddress(static_cast<HMODULE>(handle), funcName.c_str());
#else
      sym = dlsym(handle, funcName.c_str());
#endif

      if (!sym) {
#ifdef _WIN32
        std::cerr << "Error getting symbol: " << funcName
                  << " Error: " << GetLastError() << std::endl;
#else
        std::cerr << dlerror()
                  << std::endl;
#endif
        exit(1);
      }

      FuncPtr createFunc = reinterpret_cast<FuncPtr>(
          sym);
      ECS_system::ISystem *system = createFunc(
          std::forward<Args>(args)...);
      return system;
    }

    IGraphic *getGraphic(const std::string &funcName) {
      using FuncPtr =
          IGraphic *(*)(); // Function pointer type
      void *sym;

#ifdef _WIN32
      sym = GetProcAddress(static_cast<HMODULE>(handle), funcName.c_str());
#else
      sym = dlsym(handle, funcName.c_str());
#endif

      if (!sym) {
#ifdef _WIN32
        std::cerr << "Error getting symbol: " << funcName
                  << " Error: " << GetLastError() << std::endl;
#else
        std::cerr << dlerror()
                  << std::endl;
#endif
        exit(1);
      }

      FuncPtr createFunc = reinterpret_cast<FuncPtr>(
          sym);
      IGraphic *graphic = createFunc();
      return graphic;
    }

    void DLunloader() {
#ifdef _WIN32
      if (handle) {
        FreeLibrary(static_cast<HMODULE>(handle));
      }
#else
      if (handle) {
        dlclose(handle);
      }
#endif
    }
  };
};
}; // namespace rtype

#endif /* !COREMODULE_HPP_ */