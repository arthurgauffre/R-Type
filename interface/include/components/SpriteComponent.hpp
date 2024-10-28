/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SpriteComponent
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <r-type/AComponent.hpp>
#include <r-type/AGraphic.hpp>

namespace component {
class SpriteComponent : public AComponent {
public:
  /**
   * @brief Constructs a new SpriteComponent object.
   *
   * @param entityID The unique identifier for the entity.
   * @param x The x-coordinate of the sprite.
   * @param y The y-coordinate of the sprite.
   * @param graphic Reference to the IGraphic interface for handling graphics.
   */
  SpriteComponent(uint32_t entityID, float x, float y, IGraphic& graphic)
      : AComponent(entityID), _x(x), _y(y), _graphic(graphic) {
      _spriteId = _graphic.createSprite();
  }

  ~SpriteComponent() = default;

  float getX() const { return _x; }
  float getY() const { return _y; }
  uint32_t getSpriteId() const { return _spriteId; }

  void setPosition(float x, float y) {
      _x = x;
      _y = y;
      _graphic.setPosition(_spriteId, x, y);
  }
  void update(float x, float y);

private:
  float _x;
  float _y;
  uint32_t _spriteId;
  IGraphic& _graphic;
};
} // namespace component
