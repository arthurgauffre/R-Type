/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ScrollComponent
*/

#pragma once

#include <SFML/System/Vector2.hpp>
#include <r-type/AComponent.hpp>

namespace component {
class ScrollComponent : public AComponent {
public:
  ScrollComponent(uint32_t entityID, sf::Vector2f speed);
  ~ScrollComponent() = default;

  const sf::Vector2f getScrollSpeed();

  void setScrollSpeed(const sf::Vector2f &speed);

  void update(sf::Vector2f speed){
    _scrollSpeed = speed;
  };

private:
  sf::Vector2f _scrollSpeed;
};
} // namespace component