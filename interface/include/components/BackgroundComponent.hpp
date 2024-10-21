/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BackgroundComponent
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <r-type/AComponent.hpp>

namespace component
{
  class BackgroundComponent : virtual public AComponent
  {
  public:
    BackgroundComponent(uint32_t entityID, std::string texturePath,
                        const std::pair<float, float> &size);
    ~BackgroundComponent() = default;

    sf::Sprite getSprite();
    const std::pair<float, float> getSize();

    sf::Sprite getDuplicateSprite();

    void update(float deltaTime) override {};

  private:
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
     * @brief A sprite object from the SFML library used to represent the
     * background.
     *
     * This member variable holds an instance of sf::Sprite, which is used to draw
     * the background image in the game. The sf::Sprite class provides a way to
     * manipulate and display 2D images in the SFML framework.
     */
    sf::Sprite _sprite;

    /**
     * @brief A duplicate sprite used for rendering purposes.
     *
     * This sprite is a copy of the original sprite and is used to create
     * effects such as scrolling backgrounds or other visual effects that
     * require multiple instances of the same sprite.
     */
    sf::Sprite _duplicateSprite;

    /**
     * @brief A pair representing the size of the background component.
     *
     * The first element of the pair represents the width,
     * and the second element represents the height.
     */
    std::pair<float, float> _size;
  };
} // namespace component