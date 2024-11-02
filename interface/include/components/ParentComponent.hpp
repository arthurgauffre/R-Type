/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ParentComponent
*/

#pragma once

#include <r-type/AComponent.hpp>

namespace component {
class ParentComponent : public AComponent {
public:
  /**
   * @brief Constructs a new ParentComponent object.
   *
   * @param entityID The ID of the entity that this component is associated with.
   * @param parentID The ID of the parent entity.
   */
  ParentComponent(uint32_t entityID, uint32_t parentID);

  /**
   * @brief Destructor for the ParentComponent class.
   *
   * This destructor is responsible for cleaning up any resources
   * or memory allocated by the ParentComponent instance.
   */
  ~ParentComponent();

  /**
   * @brief Sets the parent ID for the component.
   *
   * @param parentID The ID of the parent to be set.
   */
  void setParentID(uint32_t parentID);

  /**
   * @brief Retrieves the ID of the parent component.
   *
   * @return uint32_t The ID of the parent component.
   */
  uint32_t getParentID();

  /**
   * @brief Updates the parent entity ID.
   *
   * This function sets the parent entity ID to the given value.
   *
   * @param parentID The new parent entity ID.
   */
  void update(uint32_t parentID) { _parentEntityID = parentID; };

private:
  /**
   * @brief The ID of the parent entity.
   *
   * This member variable stores the unique identifier of the parent entity
   * associated with this component. It is used to establish a hierarchical
   * relationship between entities in the system.
   */
  uint32_t _parentEntityID;
};
} // namespace component