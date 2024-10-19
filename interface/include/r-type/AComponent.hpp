/*
** EPITECH PROJECT, 2024
** *
** File description:
** AComponent
*/

#pragma once

#include <r-type/IComponent.hpp>

namespace component {
class AComponent : public IComponent {
public:
  /**
   * @brief Constructs an AComponent with the specified entity ID.
   *
   * This constructor initializes the component with the given entity ID
   * and sets the component's active status to true.
   *
   * @param entityID The unique identifier for the entity associated with this
   * component.
   */
  AComponent(uint32_t entityID) : id(entityID), isActive(true) {}

  /**
   * @brief Destroy the AComponent object.
   */
  virtual ~AComponent() = default;

  /**
   * @brief Retrieves the ID of the entity associated with this component.
   *
   * @return uint32_t The ID of the entity.
   */
  uint32_t getEntityID() const override { return id; }

  /**
   * @brief Retrieves the active status of the component.
   *
   * @return true if the component is active, false otherwise.
   */
  bool getActive() const override { return isActive; }

  /**
   * @brief Sets the active state of the component.
   *
   * This function overrides the base class method to set the active state
   * of the component. When a component is active, it is considered in use
   * and will participate in the system's operations.
   *
   * @param active A boolean value indicating the desired active state.
   *               - true: The component is active.
   *               - false: The component is inactive.
   */
  void setActive(bool active) override { isActive = active; }

  /**
   * @brief Update the component.
   *
   * This pure virtual function must be overridden by derived classes to update
   * the component's state.
   *
   * @param deltaTime The time elapsed since the last update, in seconds.
   */

protected:
  uint32_t id;   // Id of the associated entity
  bool isActive; // State of the component
};
} // namespace component
