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

private:
  std::pair<float, float> _size;
};
} // namespace component