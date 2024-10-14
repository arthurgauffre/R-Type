/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreModule
*/

#ifndef COREMODULE_HPP_
#define COREMODULE_HPP_

#include <iostream>
#include <limits.h>
#include <memory>
#include <r-type/ICoreModule.hpp>
#include <r-type/ISystem.hpp>
#include <unistd.h>
#include <vector>

#include <components/BackgroundComponent.hpp>
#include <components/InputComponent.hpp>
#include <components/MusicComponent.hpp>
#include <components/PositionComponent.hpp>
#include <components/ScrollComponent.hpp>
#include <components/SoundComponent.hpp>
#include <components/SpriteComponent.hpp>
#include <components/TextureComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/VelocityComponent.hpp>

#include <systems/AudioSystem.hpp>
#include <systems/RenderSystem.hpp>

namespace rtype {
class CoreModule : virtual public ICoreModule {
public:
  CoreModule();
  ~CoreModule();

  entity::IEntity *createBackground(uint32_t entityID, std::string texturePath,
                                    sf::Vector2f speed, sf::Vector2f size);
  entity::IEntity *createPlayer(uint32_t entityID, std::string texturePath,
                                sf::Vector2f position, sf::Vector2f velocity,
                                sf::Vector2f scale);

  void init();
  void run();

  std::shared_ptr<entity::EntityManager> getEntityManager() const;
  std::shared_ptr<component::ComponentManager> getComponentManager() const;
  std::shared_ptr<ECS_system::SystemManager> getSystemManager() const;

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

    template <typename... Args>
    ECS_system::ISystem *getInstance(const std::string &funcName,
                                     Args &&...args) {
      using FuncPtr =
          ECS_system::ISystem *(*)(Args...); // Function pointer type
      void *sym = dlsym(handle, funcName.c_str());

      if (!sym) {
        std::cerr << dlerror()
                  << std::endl; // Print the dynamic loader error message
        exit(1);                // Exit if symbol resolution fails
      }

      FuncPtr createFunc = reinterpret_cast<FuncPtr>(
          sym); // Cast to correct function pointer type
      return createFunc(std::forward<Args>(
          args)...); // Call function and return the shared_ptr
    }
  };
};
}; // namespace rtype

#endif /* !COREMODULE_HPP_ */