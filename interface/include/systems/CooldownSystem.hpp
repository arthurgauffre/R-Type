/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CooldownSystem
*/

#pragma once

#include <components/CooldownComponent.hpp>
#include <r-type/ASystem.hpp>

namespace ECS_system {
class CooldownSystem : virtual public ASystem {
public:
  /**
   * @class CooldownSystem
   * @brief Manages the cooldown periods for entities within the game.
   *
   * This system is responsible for handling the cooldown logic for various
   * entities, ensuring that actions are only performed after a specified
   * cooldown period has elapsed.
   *
   * @param componentManager Reference to the ComponentManager that handles
   *                         the components of the entities.
   * @param entityManager Reference to the EntityManager that manages the
   *                      entities in the game.
   * @param graphic Shared pointer to an IGraphic instance for graphical
   *                operations.
   * @param stringCom StringCom instance for communication purposes.
   */
  CooldownSystem(component::ComponentManager &componentManager,
                 entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, StringCom stringCom);

  /**
   * @brief Destructor for the CooldownSystem class.
   *
   * This destructor is responsible for cleaning up any resources
   * that the CooldownSystem class may have allocated during its
   * lifetime. It ensures that all necessary cleanup operations
   * are performed when an instance of CooldownSystem is destroyed.
   */
  ~CooldownSystem();

  /**
   * @brief Updates the cooldown system for entities.
   *
   * @param deltaTime The time elapsed since the last update.
   * @param entities A vector of shared pointers to entities that need to be updated.
   * @param msgToSend A reference to a vector of pairs containing actions and their corresponding entity IDs to be sent.
   * @param msgReceived A reference to a vector of pairs containing messages and their corresponding sender and receiver IDs.
   * @param entityMutex A mutex to ensure thread-safe access to entities.
   * @param sceneStatus A shared pointer to the current scene status.
   */
  void update(float deltaTime,
              std::vector<std::shared_ptr<entity::IEntity>> entities, std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus) override;

  /**
   * @brief Initializes the CooldownSystem.
   *
   * This function is called to initialize the CooldownSystem.
   * It overrides the base class implementation but currently does not perform any actions.
   */
  void initialize() override {}

  /**
   * @brief Handles the components associated with the CooldownSystem.
   *
   * This function is an override of a base class method and is responsible for
   * managing the components that are part of the CooldownSystem. Currently, it
   * does not perform any operations.
   */
  void handleComponents() override {}

private:
};
} // namespace ECS_system