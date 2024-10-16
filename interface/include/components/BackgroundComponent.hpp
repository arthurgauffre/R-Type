/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BackgroundComponent
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <r-type/AComponent.hpp>

namespace component {
class BackgroundComponent : virtual public AComponent {
public:
  BackgroundComponent(uint32_t entityID, std::string texturePath,
                      const sf::Vector2f &size);
  ~BackgroundComponent() = default;

  sf::Sprite getSprite();
  const sf::Vector2f getSize();

  sf::Sprite getDuplicateSprite();

  std::string getTexturePath() { return _texturePath; }

  void update(float deltaTime) override{};

private:
  /**
   * @brief A sprite object from the SFML library used to represent the
   * background.
   *
   * This member variable holds an instance of sf::Sprite, which is used to draw
   * the background image in the game. The sf::Sprite class provides a way to
   * manipulate and display 2D images in the SFML framework.
   */
  sf::Sprite _sprite;

  /**
   * @brief Holds the texture data for the background component.
   *
   * This member variable stores the texture used for rendering the background
   * in the application. It is an instance of the sf::Texture class from the
   * SFML library, which provides functionalities for loading, manipulating,
   * and drawing textures.
   */
  sf::Texture _texture;

  /**
   * @brief A duplicate sprite used for rendering purposes.
   *
   * This sprite is a copy of the original sprite and is used to create
   * effects such as scrolling backgrounds or other visual effects that
   * require multiple instances of the same sprite.
   */
  sf::Sprite _duplicateSprite;

  /**
   * @brief Represents the size of the background component.
   *
   * This member variable stores the dimensions of the background
   * as a 2D vector, where the x component represents the width
   * and the y component represents the height.
   */
  sf::Vector2f _size;

  std::string _texturePath;
};
} // namespace component