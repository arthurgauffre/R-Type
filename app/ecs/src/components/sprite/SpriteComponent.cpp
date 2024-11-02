/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SpriteComponent
*/

#include <components/SpriteComponent.hpp>
#include <memory>

/**
 * @brief Updates the position of the sprite.
 *
 * This function updates the x and y coordinates of the sprite and sets the new position
 * using the provided graphic interface.
 *
 * @param x The new x-coordinate of the sprite.
 * @param y The new y-coordinate of the sprite.
 * @param graphic A shared pointer to the graphic interface used to set the sprite position.
 */
void component::SpriteComponent::update(float x, float y, std::shared_ptr<IGraphic> graphic) {
  _x = x;
  _y = y;
  graphic->setSpritePosition(x, y, _spriteId);
}