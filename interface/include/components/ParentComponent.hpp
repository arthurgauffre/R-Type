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

private:
  uint32_t _parentEntityID;
};
} // namespace component