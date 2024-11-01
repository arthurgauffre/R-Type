/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TypeComponent
*/

#pragma once

#include <r-type/AComponent.hpp>

#include <iostream>

namespace component {
class TypeComponent : public AComponent {
public:
  TypeComponent(uint32_t entityID, Type type);
  ~TypeComponent();

  Type getType();
  void setType(Type type);

  void update(Type _type) {
    this->_type = _type;
  }

private:
  Type _type;
};
} // namespace component