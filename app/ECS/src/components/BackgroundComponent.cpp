/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BackgroundComponent
*/

#include "BackgroundComponent.hpp"

/**
 * @brief Constructs a new BackgroundComponent object.
 *
 * @param entityID The unique identifier for the entity.
 * @param texture The texture to be used for the background sprite.
 * @param size The size of the background component.
 */
component::BackgroundComponent::BackgroundComponent(uint32_t entityID,
                                                    const sf::Texture &texture,
                                                    const sf::Vector2f &size)
    : AComponent(entityID), _size(size), _sprite(texture) {
  _sprite.setScale(size.x / _sprite.getTexture()->getSize().x,
                   size.y / _sprite.getTexture()->getSize().y);
  _duplicateSprite = _sprite;
}

/**
 * @brief Retrieves the sprite associated with the BackgroundComponent.
 *
 * @return sf::Sprite The sprite representing the background.
 */
sf::Sprite component::BackgroundComponent::getSprite() { return _sprite; }

/**
 * @brief Retrieves the size of the background component.
 *
 * @return sf::Vector2f The size of the background component.
 */
const sf::Vector2f component::BackgroundComponent::getSize() { return _size; }

/**
 * @brief Retrieves a duplicate sprite of the background component.
 *
 * @return sf::Sprite A duplicate sprite of the background component.
 */
sf::Sprite component::BackgroundComponent::getDuplicateSprite() {
  return _duplicateSprite;
}