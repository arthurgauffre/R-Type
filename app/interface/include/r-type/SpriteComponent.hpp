/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SpriteComponent
*/

#pragma once

#include <r-type/AComponent.hpp>
#include <SFML/Graphics.hpp>

namespace component {
class SpriteComponent : public AComponent {
public:
  /**
   * @brief Constructs a new SpriteComponent object.
   *
   * @param entityID The unique identifier for the entity.
   * @param x The x-coordinate of the sprite.
   * @param y The y-coordinate of the sprite.
   */
  SpriteComponent(uint32_t entityID, float x, float y)
      : AComponent(entityID), _x(x), _y(y){};

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
  sf::Sprite &getSprite() { return _sprite; }

  void update(float deltaTime) override;

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
  sf::Sprite _sprite;
};
} // namespace component