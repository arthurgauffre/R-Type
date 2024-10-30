/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionSystem
*/

#pragma once

#include <components/HealthComponent.hpp>
#include <components/HitBoxComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/TypeComponent.hpp>
#include <components/DamageComponent.hpp>
#include <r-type/ASystem.hpp>

#include <iostream>
#include <memory>
#include <vector>

namespace ECS_system {
class CollisionSystem : virtual public ASystem {
public:
  /**
   * @brief Constructs a new CollisionSystem object.
   *
   * @param componentManager Reference to the ComponentManager that manages the
   * components.
   */
  CollisionSystem(component::ComponentManager &componentManager,
                  entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic)
      : ASystem(componentManager, entityManager, graphic) {}

  /**
   * @brief Destroys the CollisionSystem object.
   */
  ~CollisionSystem() = default;

  /**
   * @brief Updates the collision system for the given entities.
   *
   * This function is called to update the state of the collision system based
   * on the elapsed time and the list of entities provided. It overrides the
   * base class update method.
   *
   * @param deltaTime The time elapsed since the last update, in seconds.
   * @param entities A vector of shared pointers to the entities that need to be
   * updated.
   */
  void
  update(float deltaTime,
         std::vector<std::shared_ptr<entity::IEntity>> entities,
         std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<entity::SceneStatus> &sceneStatus) override;

  /**
   * @brief Initializes the collision system.
   *
   * This method is called to set up any necessary resources or configurations
   * for the collision system. It overrides the base class implementation.
   */
  void initialize() override{};

  /**
   * @brief Handles the collision components within the ECS framework.
   *
   * This function is an override of the base class method and is responsible
   * for managing and updating the collision components in the system. The
   * actual implementation details should be provided in the function body.
   */
  void handleComponents() override{};

private:
  /**
   * @brief Handles the collision between two hitboxes.
   *
   * This function processes the collision logic between two given hitbox
   * components. It determines the outcome of the collision and applies
   * necessary changes to the involved entities.
   *
   * @param hitbox1 Pointer to the first hitbox component involved in the
   * collision.
   * @param hitbox2 Pointer to the second hitbox component involved in the
   * collision.
   */
  void handleCollision(entity::IEntity *entity1, entity::IEntity *entity2);

  /**
   * @brief Checks if two hitboxes are colliding.
   *
   * This function determines whether two hitboxes, represented by
   * HitBoxComponent objects, are intersecting or overlapping.
   *
   * @param hitbox1 Pointer to the first HitBoxComponent.
   * @param hitbox2 Pointer to the second HitBoxComponent.
   * @return true if the hitboxes are colliding, false otherwise.
   */
  bool isColliding(component::HitBoxComponent *hitbox1,
                   component::HitBoxComponent *hitbox2);
};
} // namespace ECS_system