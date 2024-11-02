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
   * @brief Retrieves the communication status of the component.
   *
   * This method is used to determine the current communication status of the
   * component.
   *
   * @return ComponentCommunication The current communication status of the
   * component.
   */
  ComponentCommunication getCommunication() const override { return _communication; }

  /**
   * @brief Sets the communication status of the component.
   *
   * This method is used to set the communication status of the component.
   *
   * @param communication The new communication status of the component.
   */
  void setCommunication(ComponentCommunication communication) override { _communication = communication; }

protected:
  /**
   * @brief Unique identifier for the component.
   */
  uint32_t id;

  /**
   * @brief Indicates whether the component is active or not.
   */
  bool isActive;
};
} // namespace component
