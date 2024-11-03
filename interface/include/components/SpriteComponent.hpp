/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SpriteComponent
*/

#pragma once

#include <r-type/AComponent.hpp>

namespace component {
/**
 * @class SpriteComponent
 * @brief A component that represents a sprite in the game.
 *
 * The SpriteComponent class is responsible for managing the position, color, and graphical representation
 * of a sprite associated with an entity in the game. It inherits from the AComponent class.
 *
 * @note This class uses a shared pointer to an IGraphic interface for graphical operations.
 *
 * @fn SpriteComponent::SpriteComponent(uint32_t entityID, float x, float y, RColor color, std::shared_ptr<IGraphic> graphic)
 * @brief Constructs a new SpriteComponent object.
 * @param entityID The unique identifier for the entity.
 * @param x The x-coordinate of the sprite.
 * @param y The y-coordinate of the sprite.
 * @param color The color of the sprite.
 * @param graphic A shared pointer to an IGraphic interface for graphical operations.
 *
 * @fn SpriteComponent::~SpriteComponent()
 * @brief Default destructor for the SpriteComponent class.
 *
 * @fn float SpriteComponent::getX() const
 * @brief Get the x position of the sprite.
 * @return The x position as a float.
 *
 * @fn float SpriteComponent::getY() const
 * @brief Get the y position of the sprite.
 * @return The y position as a float.
 *
 * @fn size_t& SpriteComponent::getSpriteId()
 * @brief Get the sprite object.
 * @return The sprite object as a reference to a size_t.
 *
 * @fn void SpriteComponent::update(float x, float y, std::shared_ptr<IGraphic> graphic)
 * @brief Update the position and graphical representation of the sprite.
 * @param x The new x-coordinate of the sprite.
 * @param y The new y-coordinate of the sprite.
 * @param graphic A shared pointer to an IGraphic interface for graphical operations.
 *
 * @fn RColor SpriteComponent::getColor() const
 * @brief Get the color of the sprite.
 * @return The color of the sprite as an RColor.
 *
 * @var SpriteComponent::_x
 * @brief Represents the x-coordinate of the sprite.
 *
 * @var SpriteComponent::_y
 * @brief Represents the y-coordinate of the sprite.
 *
 * @var SpriteComponent::_spriteId
 * @brief Represents the sprite object.
 *
 * @var SpriteComponent::_color
 * @brief Represents the color of the sprite.
 */
class SpriteComponent : virtual public AComponent {
public:
  /**
   * @brief Constructs a new SpriteComponent object.
   *
   * @param entityID The unique identifier for the entity.
   * @param x The x-coordinate of the sprite.
   * @param y The y-coordinate of the sprite.
   */
  SpriteComponent(uint32_t entityID, float x, float y, RColor color, std::shared_ptr<IGraphic> graphic)
      : AComponent(entityID), _x(x), _y(y){
        _spriteId = graphic->createSprite();
        _color = color;
        graphic->setSpriteColor(_spriteId, color);
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

  /**
   * @brief Updates the position of the sprite and performs any necessary graphic updates.
   *
   * @param x The new x-coordinate of the sprite.
   * @param y The new y-coordinate of the sprite.
   * @param graphic A shared pointer to the graphic interface used for rendering.
   */
  void update(float x, float y, std::shared_ptr<IGraphic> graphic);

  /**
   * @brief Get the color of the sprite.
   *
   * @return RColor The color of the sprite.
   */
  RColor getColor() const { return _color; }

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

  /**
   * @brief Represents the color of the sprite.
   */
  RColor _color;
};
} // namespace component