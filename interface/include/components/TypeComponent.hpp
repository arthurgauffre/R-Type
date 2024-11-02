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
  /**
   * @brief Constructs a new TypeComponent object.
   *
   * @param entityID The unique identifier for the entity.
   * @param type The type associated with this component.
   */
  TypeComponent(uint32_t entityID, Type type);

  /**
   * @brief Destructor for the TypeComponent class.
   */
  ~TypeComponent();

  /**
   * @brief Retrieves the type of the component.
   *
   * @return Type The type of the component.
   */
  Type getType();

  /**
   * @brief Sets the type of the component.
   *
   * @param type The type to set for the component.
   */
  void setType(Type type);

  /**
   * @brief Updates the type of the component.
   *
   * @param _type The new type to be set.
   */
  void update(Type _type) {
    this->_type = _type;
  }

private:
  /**
   * @brief Represents the type of the component.
   *
   * This member variable holds the type information for the component.
   * The type is defined by the Type enumeration or class.
   */
  Type _type;
};
} // namespace component