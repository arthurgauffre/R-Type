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
  ParentComponent(uint32_t entityID, uint32_t parentID);
  ~ParentComponent();

  void setParentID(uint32_t parentID);
  uint32_t getParentID();

  void update(float deltaTime) override {}

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