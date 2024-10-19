/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ScrollComponent
*/

#include <components/ScrollComponent.hpp>

component::ScrollComponent::ScrollComponent(uint32_t entityID,
                                            std::pair<float, float> speed)
    : AComponent(entityID), _scrollSpeed(speed) {}

const std::pair<float, float> component::ScrollComponent::getScrollSpeed()
{
  return _scrollSpeed;
}

void component::ScrollComponent::setScrollSpeed(const std::pair<float, float> &speed)
{
  _scrollSpeed = speed;
}