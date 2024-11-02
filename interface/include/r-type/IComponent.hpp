/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IComponent
*/

#pragma once

#include <cstdint>
#include <r-type/IGraphic.hpp>

namespace component {
enum class ComponentCommunication {
  NONE,
  CREATE,
  UPDATE,
  DELETE,
  SERVERONLY,
  CLIENTONLY,
  STANDBY,
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

  /**
   * @brief Retrieves the communication status of the component.
   *
   * This method is used to determine the current communication status of the
   * component.
   *
   * @return ComponentCommunication The current communication status of the
   * component.
   */
  virtual ComponentCommunication getCommunication() const = 0;

  /**
   * @brief Sets the communication status of the component.
   *
   * This method is used to set the communication status of the component.
   *
   * @param communication The new communication status of the component.
   */
  virtual void setCommunication(ComponentCommunication communication) = 0;

  protected:
    /**
     * @brief Represents the communication type for a component.
     *
     * This member variable is used to specify the type of communication
     * that a component will use. It is initialized with the value
     * ComponentCommunication::CREATE.
     */
    ComponentCommunication _communication{ComponentCommunication::CREATE};
};
} // namespace component