/*
** EPITECH PROJECT, 2024
** *
** File description:
** AEntity
*/

#pragma once

#include <r-type/IEntity.hpp>

namespace entity {
class AEntity : public IEntity {
public:
  /**
   * @brief Constructs an AEntity object with a specified ID and sets it as
   * active.
   *
   * @param id The unique identifier for the entity.
   */
  AEntity(uint32_t id) : id(id), isActive(true) {}

  /**
   * @brief Destroy the AEntity object.
   */
  virtual ~AEntity() = default;

  /**
   * @brief Retrieves the unique identifier of the entity.
   *
   * @return uint32_t The unique identifier of the entity.
   */
  uint32_t getID() const override { return id; }

  /**
   * @brief Sets the active state of the entity.
   *
   * This function overrides the base class implementation to set the active
   * state of the entity. When an entity is active, it is considered in use and
   * will be processed by the system. When inactive, it will be ignored.
   *
   * @param active A boolean value indicating the desired active state.
   *               - true: The entity is active.
   *               - false: The entity is inactive.
   */
  void setActive(bool active) override { isActive = active; }

  /**
   * @brief Retrieves the active status of the entity.
   *
   * @return true if the entity is active, false otherwise.
   */
  bool getActive() const override { return isActive; }

protected:
  /**
   * @brief Unique identifier for the entity.
   *
   * This ID is used to distinguish each entity within the ECS (Entity Component
   * System).
   */
  uint32_t id;

  /**
   * @brief Indicates whether the entity is currently active.
   *
   * This boolean flag is used to determine if the entity is active and should
   * be processed in the game loop. If set to true, the entity is active; if
   * false, the entity is inactive.
   */
  bool isActive;
};
} // namespace entity