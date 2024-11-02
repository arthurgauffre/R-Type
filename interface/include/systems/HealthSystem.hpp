/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HealthSystem
*/

#pragma once

#include <r-type/ASystem.hpp>

#include <components/HealthComponent.hpp>

namespace ECS_system {
class HealthSystem : virtual public ASystem {
public:
  /**
   * @class HealthSystem
   * @brief Manages the health components of entities within the game.
   *
   * This system is responsible for updating and maintaining the health status
   * of entities. It interacts with the component manager to access health
   * components and the entity manager to manage entity states.
   *
   * @param componentManager Reference to the component manager to access components.
   * @param entityManager Reference to the entity manager to manage entities.
   * @param graphic Shared pointer to the graphic interface for rendering purposes.
   * @param stringCom String communication object for handling string-based messages.
   */
  HealthSystem(component::ComponentManager &componentManager,
               entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, std::shared_ptr<IAudio> audio, StringCom stringCom);

  /**
   * @brief Destructor for the HealthSystem class.
   *
   * This destructor is responsible for cleaning up any resources
   * that the HealthSystem class may have allocated during its lifetime.
   */
  ~HealthSystem();

  /**
   * @brief Updates the health system for all entities.
   *
   * @param deltaTime The time elapsed since the last update.
   * @param entities A vector of shared pointers to the entities to be updated.
   * @param msgToSend A reference to a vector of pairs containing actions and entity IDs to send messages.
   * @param msgReceived A reference to a vector of pairs containing received messages with their corresponding entity IDs.
   * @param entityMutex A reference to a mutex for synchronizing access to entities.
   * @param sceneStatus A shared pointer to the current scene status.
   */
  void
  update(float deltaTime,
         std::vector<std::shared_ptr<entity::IEntity>> entities,
         std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus) override;

  /**
   * @brief Initializes the health system.
   *
   * This method is called to set up the health system. It overrides the base class
   * implementation. Currently, it does not perform any specific actions.
   */
  void initialize() override{};

  /**
   * @brief Handles the components associated with the health system.
   *
   * This function is intended to manage and update the components related to the health system.
   * It overrides a base class method to provide specific functionality for health components.
   */
  void handleComponents() override{};

private:
};
} // namespace ECS_system