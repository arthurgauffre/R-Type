/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ScrollComponent
*/

#pragma once

#include <r-type/AComponent.hpp>
#include <utility>

namespace component
{
  class ScrollComponent : public AComponent
  {
  public:
    ScrollComponent(uint32_t entityID, std::pair<float, float> speed);
    ~ScrollComponent() = default;

    const std::pair<float, float> getScrollSpeed();

    void setScrollSpeed(const std::pair<float, float> &speed);

    void update(float deltaTime) override {};

  private:
    std::pair<float, float> _scrollSpeed;
  };
} // namespace component