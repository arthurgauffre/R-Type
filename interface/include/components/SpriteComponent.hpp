/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SpriteComponent
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <r-type/AComponent.hpp>

namespace component {
class SpriteComponent : virtual public AComponent {
public:
  /**
   * @brief Constructs a new SpriteComponent object.
   *
   * @param entityID The unique identifier for the entity.
   * @param x The x-coordinate of the sprite.
   * @param y The y-coordinate of the sprite.
   */
  SpriteComponent(uint32_t entityID, float x, float y, std::shared_ptr<IGraphic> graphic)
      : AComponent(entityID), _x(x), _y(y){
        _spriteId = graphic->createSprite();
      };

  /**
   * @brief Default destructor for the SpriteComponent class.
   */
  ~SpriteComponent() = default;

  /**
   * @brief Get the x position of the sprite.
   *
   * @return The x position as a float.
   */
  float getX() const { return _x; }

  /**
   * @brief Get the y position of the sprite.
   *
   * @return The y position as a float.
   */
  float getY() const { return _y; }

  /**
   * @brief Get the sprite object.
   *
   * @return sf::Sprite& The sprite object.
   */
  size_t &getSpriteId() { return _spriteId; }

  void update(float x, float y, std::shared_ptr<IGraphic> graphic);

private:
  /**
   * @brief Represents the x-coordinate of the sprite.
   */
  float _x;

  /**
   * @brief Represents the y-coordinate of the sprite.
   */
  float _y;

  /**
   * @brief Represents the sprite object.
   */
  size_t _spriteId;
};
} // namespace component