/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MovementSystem
*/

#pragma once

#include <SFML/System/Time.hpp>
#include <components/BackgroundComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/TypeComponent.hpp>
#include <components/VelocityComponent.hpp>
#include <r-type/ASystem.hpp>

namespace ECS_system {
class MovementSystem : public ASystem {
public:
  /**
   * @class MovementSystem
   * @brief A system responsible for handling the movement of entities.
   *
   * This class inherits from ASystem and is used to manage and update the
   * movement-related components of entities within the ECS framework.
   *
   * @param componentManager A reference to the ComponentManager that manages
   *                         all components in the ECS.
   */
  MovementSystem(component::ComponentManager &componentManager,
                 entity::EntityManager &entityManager)
      : ASystem(componentManager, entityManager) {}

  /**
   * @brief Default destructor for the MovementSystem class.
   *
   */
  ~MovementSystem() = default;

  /**
   * @brief Initializes the MovementSystem.
   *
   * This function initializes the MovementSystem by setting up any required
   * resources or state.
   */
  void initialize() override{};

  /**
   * @brief Updates the MovementSystem.
   *
   * This function updates the MovementSystem based on the elapsed time and the
   * entities provided.
   *
   * @param deltaTime The time elapsed since the last update, in seconds.
   * @param entities A vector of shared pointers to the entities to be updated.
   */
  void
  update(float deltaTime,
         std::vector<std::shared_ptr<entity::IEntity>> entities,
         std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, size_t>> &msgReceived) override;

  /**
   * @brief Handles the components of the MovementSystem.
   *
   * This function handles the components of the MovementSystem by updating the
   * position of entities based on their velocity.
   */
  void handleComponents() override{};

protected:
private:
};
} // namespace ECS_system