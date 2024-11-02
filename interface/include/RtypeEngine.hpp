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
#include <Clock.hpp>
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
#include <components/RectangleShapeComponent.hpp>
#include <components/OnClickComponent.hpp>
#include <components/TextComponent.hpp>

#include <r-type/IGraphic.hpp>
#include <r-type/Enum.hpp>

namespace rtype {
class RtypeEngine : virtual public IRtypeEngine {
public:
/**
 * @brief Constructs a new RtypeEngine object with the specified graphic name.
 *
 * @param graphicName The name of the graphic to be used by the engine.
 */
  RtypeEngine(std::string graphicName);

/**
 * @brief Destructor for the RtypeEngine class.
 *
 * This destructor is responsible for cleaning up any resources
 * that the RtypeEngine class may have allocated during its lifetime.
 */
  ~RtypeEngine();

/**
 * @brief Updates the state of the R-Type engine.
 *
 * This function is responsible for updating the internal state of the R-Type engine.
 * It should be called regularly to ensure the engine's state is kept up-to-date.
 */
  void update();

/**
 * @brief Starts the R-Type game engine.
 *
 * This function initializes and runs the main game loop, handling all game
 * logic, rendering, and updates. It should be called to start the game.
 */
  void run();

/**
 * @brief Retrieves the EntityManager instance.
 *
 * This function returns a shared pointer to the EntityManager, which is responsible
 * for managing all entities within the R-Type engine. The EntityManager handles
 * creation, deletion, and updates of entities.
 *
 * @return std::shared_ptr<entity::EntityManager> A shared pointer to the EntityManager instance.
 */
  std::shared_ptr<entity::EntityManager> getEntityManager() const;

/**
 * @brief Retrieves the component manager.
 *
 * This function returns a shared pointer to the component manager, which is responsible
 * for managing all the components within the engine.
 *
 * @return std::shared_ptr<component::ComponentManager> A shared pointer to the component manager.
 */
  std::shared_ptr<component::ComponentManager> getComponentManager() const;

/**
 * @brief Retrieves the system manager.
 *
 * This function returns a shared pointer to the SystemManager instance.
 * The SystemManager is responsible for managing all the systems within the ECS (Entity Component System).
 *
 * @return std::shared_ptr<ECS_system::SystemManager> A shared pointer to the SystemManager.
 */
  std::shared_ptr<ECS_system::SystemManager> getSystemManager() const;

/**
 * @brief A vector that stores pairs of messages and their associated metadata.
 *
 * Each element in the vector is a pair where:
 * - The first element is a string representing the message.
 * - The second element is a pair of size_t values representing metadata associated with the message.
 *   - The first size_t value could represent a timestamp or an identifier.
 *   - The second size_t value could represent a length or another identifier.
 */
  std::vector<std::pair<std::string, std::pair<size_t, size_t>>> msgReceived;

/**
 * @brief A vector of pairs where each pair consists of an Action and a size_t.
 *
 * This vector is used to store messages to be sent, where each message is
 * represented by an Action and its associated size.
 */
  std::vector<std::pair<Action, size_t>> msgToSend;
  rtype::Clock clock;
  std::mutex _entityMutex;

/**
 * @brief A shared pointer to an IGraphic object.
 *
 * This member variable holds a shared pointer to an instance of a class
 * that implements the IGraphic interface. It is used to manage the
 * graphical components of the application, ensuring proper memory
 * management and shared ownership.
 */
  std::shared_ptr<IGraphic> _graphic;

  template <typename T> class DLLoader {
  public:
    void *handle;

/**
 * @brief Constructor for the DLLoader class.
 *
 * This constructor attempts to load a dynamic library from the specified path.
 * On Windows, it uses LoadLibrary, and on other platforms, it uses dlopen.
 * If the library fails to load, an error message is printed to stderr and the program exits.
 *
 * @param libPath The path to the dynamic library to be loaded.
 */
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

/**
 * @brief Destructor for the DLLoader class.
 *
 * This destructor is responsible for cleaning up any resources
 * that the DLLoader class may have allocated during its lifetime.
 */
    ~DLLoader() {}

/**
 * @brief Retrieves a system from a dynamically loaded library.
 *
 * This function attempts to retrieve a system creation function from a dynamically
 * loaded library using the provided function name and arguments. It supports both
 * Windows and Unix-like systems.
 *
 * @tparam Args The types of the arguments to be passed to the system creation function.
 * @param funcName The name of the function to retrieve from the dynamically loaded library.
 * @param args The arguments to be forwarded to the system creation function.
 * @return A pointer to the created system.
 *
 * @throws std::runtime_error If the symbol cannot be found in the dynamically loaded library.
 */
    template <typename... Args>
    ECS_system::ISystem *getSystem(const std::string &funcName,
                                     Args &&...args) {
      using FuncPtr =
          ECS_system::ISystem *(*)(Args...);
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

/**
 * @brief Retrieves a graphic object by dynamically loading a function from a shared library.
 *
 * This function attempts to load a symbol (function) from a shared library (DLL on Windows,
 * shared object on Unix-like systems) and then calls this function to get an instance of
 * IGraphic.
 *
 * @param funcName The name of the function to load from the shared library.
 * @return IGraphic* A pointer to the IGraphic object created by the loaded function.
 *
 * @note The function will terminate the program if the symbol cannot be loaded.
 *
 * @warning Ensure that the shared library is correctly loaded and the function name is correct.
 *          On failure, the function will print an error message to stderr and exit the program.
 */
    IGraphic *getGraphic(const std::string &funcName) {
      using FuncPtr =
          IGraphic *(*)();
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

/**
 * @brief Unloads the dynamic library associated with the handle.
 *
 * This function checks if the handle is valid and then unloads the dynamic library.
 * It uses platform-specific functions to perform the unloading:
 * - On Windows, it uses FreeLibrary.
 * - On other platforms, it uses dlclose.
 */
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