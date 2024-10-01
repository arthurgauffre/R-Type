/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TextureComponent
*/

#pragma once

#include <r-type/AComponent.hpp>
#include <SFML/Graphics.hpp>

namespace component {
class TextureComponent : public AComponent {
public:
  TextureComponent(uint32_t entityID, const std::string &path)
      : AComponent(entityID) {
    _texture.loadFromFile(path);
  }

  /**
   * @brief Default destructor for the TextureComponent class.
   */
  ~TextureComponent() = default;

  /**
   * @brief Retrieves the texture associated with this component.
   *
   * @return Reference to the sf::Texture object.
   */
  sf::Texture &getTexture() { return _texture; }

  /**
   * @brief Updates the texture component.
   *
   * This function is called to update the state of the texture component
   * based on the elapsed time since the last update.
   *
   * @param deltaTime The time elapsed since the last update, in seconds.
   */
  void update(float deltaTime) override;

private:
  /**
   * @brief Represents a texture in the SFML library.
   *
   * This component holds an instance of sf::Texture, which is used to load and
   * manage graphical textures in the application. Textures are used to draw
   * images, sprites, and other graphical elements.
   *
   * @see sf::Texture
   */
  sf::Texture _texture;
};
} // namespace component
