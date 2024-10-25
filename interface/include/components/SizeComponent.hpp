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
  SizeComponent(uint32_t entityID, std::pair<float, float> size);
  ~SizeComponent();

  void setSize(const std::pair<float, float> &size);
  const std::pair<float, float> getSize();

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