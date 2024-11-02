/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SizeComponent
*/

#pragma once

#include <r-type/AComponent.hpp>

#include <utility>

namespace component {
class SizeComponent : public AComponent {
public:
  /**
   * @brief Constructs a new SizeComponent object.
   *
   * @param entityID The unique identifier for the entity.
   * @param size A pair representing the width and height of the entity.
   */
  SizeComponent(uint32_t entityID, std::pair<float, float> size);

  /**
   * @brief Destructor for the SizeComponent class.
   */
  ~SizeComponent();

  /**
   * @brief Sets the size of the component.
   *
   * @param size A pair of floats representing the width and height of the component.
   */
  void setSize(const std::pair<float, float> &size);

  /**
   * @brief Retrieves the size of the component.
   *
   * @return A std::pair containing the width and height of the component as floats.
   */
  const std::pair<float, float> getSize();

  /**
   * @brief Updates the size of the component.
   *
   * @param size A pair of floats representing the new size (width, height).
   */
  void update(std::pair<float, float> size) {
    _size = size;
  }

private:
  /**
   * @brief Represents the size of a component.
   *
   * This member variable stores the width and height of a component
   * as a pair of floating-point values.
   *
   * @var _size
   * @type std::pair<float, float>
   */
  std::pair<float, float> _size;
};
} // namespace component