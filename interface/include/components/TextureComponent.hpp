/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TextureComponent
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <r-type/AComponent.hpp>

namespace component {
class TextureComponent : public AComponent {
public:
  /**
   * @brief Constructs a new TextureComponent object.
   *
   * This constructor initializes a TextureComponent with the given entity ID
   * and loads a texture from the specified file path.
   *
   * @param entityID The unique identifier for the entity associated with this
   * component.
   * @param path The file path to the texture to be loaded.
   */
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
