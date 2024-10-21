/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IComponent
*/

#pragma once

#include <cstdint>

namespace component {
enum class ComponentCommunication {
  NONE,
  CREATE,
  UPDATE,
  DELETE,
};

class IComponent {
public:
  /*
  ** @brief Virtual destructor for the IComponent class.
  */
  virtual ~IComponent() = default;

  /**
   * @brief Retrieves the ID of the entity associated with this component.
   *
   * @return uint32_t The ID of the entity.
   */
  virtual uint32_t getEntityID() const = 0;

  /**
   * @brief Retrieve the active status of the component.
   *
   * This pure virtual function must be implemented by derived classes
   * to indicate whether the component is currently active.
   *
   * @return true if the component is active, false otherwise.
   */
  virtual bool getActive() const = 0;

  /**
   * @brief Sets the active state of the component.
   *
   * This method is used to enable or disable the component.
   *
   * @param active A boolean value where true activates the component and false
   * deactivates it.
   */
  virtual void setActive(bool active) = 0;
};
} // namespace component