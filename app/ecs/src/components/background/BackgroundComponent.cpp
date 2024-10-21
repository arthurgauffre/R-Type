/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BackgroundComponent
*/

#include <components/BackgroundComponent.hpp>

#include <iostream>

/**
 * @brief Constructs a new BackgroundComponent object.
 *
 * This constructor initializes a BackgroundComponent with the specified entity
 * ID, texture path, and size. It loads the texture from the given file path and
 * sets it to the sprite and duplicate sprite. The sprite and duplicate sprite
 * are then scaled according to the provided size.
 *
 * @param entityID The unique identifier for the entity.
 * @param texturePath The file path to the texture to be loaded.
 * @param size A pair representing the width and height to scale the sprite.
 *
 * @throws std::runtime_error If the texture cannot be loaded from the specified
 * file path.
 */
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