/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TextureComponent
*/

#pragma once

#include <r-type/AComponent.hpp>
#include <memory>

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
  TextureComponent(uint32_t entityID, const std::string &path, std::shared_ptr<IGraphic> graphic)
      : AComponent(entityID) {
    _path = path;
    _textureId = graphic->createTexture(path);
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
  size_t &getTexture() { return _textureId; }

  /**
   * @brief Retrieves the path to the texture file.
   *
   * @return The path to the texture file.
   */
  std::string getPath() { return _path; }

  /**
   * @brief Updates the texture component.
   *
   * This function is called to update the state of the texture component
   * based on the elapsed time since the last update.
   *
   * @param deltaTime The time elapsed since the last update, in seconds.
   */
  void update(std::string &path, std::shared_ptr<IGraphic> graphic);

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
  size_t _textureId;

  /**
   * @brief The file path to the texture.
   */
  std::string _path;
};
} // namespace component
