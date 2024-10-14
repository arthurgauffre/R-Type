/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ScrollComponent
*/

#include <components/ScrollComponent.hpp>

component::ScrollComponent::ScrollComponent(uint32_t entityID,
                                            sf::Vector2f speed)
    : AComponent(entityID), _scrollSpeed(speed) {}

const sf::Vector2f component::ScrollComponent::getScrollSpeed() {
  return _scrollSpeed;
}

void component::ScrollComponent::setScrollSpeed(const sf::Vector2f &speed) {
  _scrollSpeed = speed;
}