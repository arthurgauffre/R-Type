/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SpriteComponent
*/

#include <components/SpriteComponent.hpp>

void component::SpriteComponent::update(float x, float y) {
  _x = x;
  _y = y;
  _sprite.setPosition(x, y);
  // Update the component
}