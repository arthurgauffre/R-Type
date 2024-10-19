/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BackgroundComponent
*/

#include <components/BackgroundComponent.hpp>

#include <iostream>

component::BackgroundComponent::BackgroundComponent(
    uint32_t entityID, std::string texturePath,
    const std::pair<float, float> &size)
    : AComponent(entityID), _size(size) {
  if (!_texture.loadFromFile(texturePath)) {
    throw std::runtime_error("Could not load texture from file: " +
                             texturePath);
  }
  _sprite.setTexture(_texture);
  _duplicateSprite.setTexture(_texture);
  _sprite.setScale(size.first / _sprite.getTexture()->getSize().x,
                   size.second / _sprite.getTexture()->getSize().y);
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
 * @return std::pair <float, float> The size of the background component.
 */
const std::pair<float, float> component::BackgroundComponent::getSize() {
  return _size;
}

/**
 * @brief Retrieves a duplicate sprite of the background component.
 *
 * @return sf::Sprite A duplicate sprite of the background component.
 */
sf::Sprite component::BackgroundComponent::getDuplicateSprite() {
  return _duplicateSprite;
}