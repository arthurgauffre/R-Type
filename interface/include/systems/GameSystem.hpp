/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameSystem
*/

#pragma once

#include <Error.hpp>
#include <r-type/ASystem.hpp>

#include <components/TypeComponent.hpp>

namespace ECS_system {
class GameSystem : virtual public ASystem {
public:
  /**
   * @brief Constructs a new GameSystem object.
   *
   * @param componentManager Reference to the ComponentManager instance.
   * @param entityManager Reference to the EntityManager instance.
   * @param graphic Shared pointer to an IGraphic instance.
   * @param stringCom StringCom object.
   */
  GameSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, std::shared_ptr<IAudio> audio, StringCom stringCom);

  /**
   * @brief Destructor for the GameSystem class.
   *
   * This destructor is responsible for cleaning up resources
   * used by the GameSystem instance before it is destroyed.
   */
  ~GameSystem();

  /**
   * @brief Updates the game system.
   *
   * This function updates the game system based on the elapsed time, the list of entities,
   * messages to send, messages received, and the current scene status.
   *
   * @param deltaTime The time elapsed since the last update.
   * @param entities A vector of shared pointers to the entities in the game.
   * @param msgToSend A reference to a vector of pairs containing actions and their corresponding entity IDs to be sent.
   * @param msgReceived A reference to a vector of pairs containing messages and their corresponding sender and receiver IDs.
   * @param entityMutex A reference to a mutex for synchronizing access to the entities.
   * @param sceneStatus A shared pointer to the current scene status.
   */
  void update(float deltaTime,
              std::vector<std::shared_ptr<entity::IEntity>> entities, std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus) override;

  /**
   * @brief Initializes the game system.
   *
   * This method is called to perform any necessary setup or initialization
   * for the game system. It is an override of a base class method.
   */
  void initialize() override {}

  /**
   * @brief Handles the components of the game system.
   *
   * This function is an override of a virtual function in the base class.
   * It is responsible for managing the components associated with the game system.
   */
  void handleComponents() override {}

protected:
private:
};
} // namespace ECS_system