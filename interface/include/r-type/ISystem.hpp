/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Isystem
*/

#pragma once

#include <r-type/Enum.hpp>
#include <managers/ComponentManager.hpp>
#include <managers/EntityManager.hpp>
#include <memory>
#include <r-type/IEntity.hpp>
#include <r-type/IGraphic.hpp>
#include <r-type/IAudio.hpp>
#include <vector>
#include <mutex>

#ifdef _WIN32
#define EXPORT_API extern "C" __declspec(dllexport)
#else
#define EXPORT_API extern "C"
#endif

namespace ECS_system {
/**
 * @struct StringCom
 * @brief A structure to hold mappings of various types to their corresponding string representations.
 *
 * This structure contains three unordered maps:
 * - texturePath: Maps TexturePath to its corresponding string.
 * - textFont: Maps TextFont to its corresponding string.
 * - textString: Maps TextString to its corresponding string.
 */
struct StringCom {
  std::unordered_map<TexturePath, std::string> texturePath;
  std::unordered_map<TextFont, std::string> textFont;
  std::unordered_map<TextString, std::string> textString;
  std::unordered_map<SoundPath, std::string> soundPath;
};
class ISystem {
public:
  ISystem(component::ComponentManager &componentManager,
          entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, std::shared_ptr<IAudio> audio, StringCom stringCom)
      : _componentManager(componentManager), _entityManager(entityManager), _graphic(graphic), _audio(audio), _stringCom(stringCom) {}
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
         std::vector<std::shared_ptr<entity::IEntity>> entities,
         std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus) = 0;

  /**
   * @brief Pure virtual function to handle the components of the system.
   *
   * This function must be overridden by any derived class to define the
   * specific behavior for handling components within the system.
   */
  virtual void handleComponents() = 0;

protected:
  /**
   * @brief Reference to the ComponentManager instance.
   *
   * This member variable holds a reference to the ComponentManager, which is responsible
   * for managing all the components within the system. It provides functionalities to
   * add, remove, and query components.
   */
  component::ComponentManager &_componentManager;

  /**
   * @brief Reference to the EntityManager instance.
   *
   * This member variable holds a reference to the EntityManager, which is responsible
   * for managing all entities within the system. It provides functionalities such as
   * adding, removing, and updating entities.
   */
  entity::EntityManager &_entityManager;

  /**
   * @brief A shared pointer to an IGraphic instance.
   *
   * This member variable holds a shared pointer to an object that implements
   * the IGraphic interface. It is used to manage the graphical components
   * within the system, ensuring proper memory management and resource sharing.
   */
  std::shared_ptr<IGraphic> _graphic;

  std::shared_ptr<IAudio> _audio;

  /**
   * @brief A member variable of type StringCom.
   *
   * This variable is used to store and manage string communications within the system.
   */
  StringCom _stringCom;
};
} // namespace ECS_system
