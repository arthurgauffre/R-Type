/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SpriteComponent
*/

#include <components/SpriteComponent.hpp>
#include <memory>

void component::SpriteComponent::update(float x, float y, std::shared_ptr<IGraphic> graphic) {
  _x = x;
  _y = y;
  graphic->setSpritePosition(x, y, _spriteId);
}