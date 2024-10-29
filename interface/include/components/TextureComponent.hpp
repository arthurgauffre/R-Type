/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TextureComponent
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <r-type/AComponent.hpp>
#include <r-type/AGraphic.hpp>

namespace component {
class TextureComponent : public AComponent {
public:
  /**
   * @brief Constructs a new TextureComponent object.
   *
   * @param entityID The unique identifier for the entity.
   * @param path The file path to the texture to be loaded.
   * @param graphic Reference to the IGraphic interface for handling graphics.
   */
  TextureComponent(uint32_t entityID, const std::string &path, IGraphic& graphic)
      : AComponent(entityID), _graphic(graphic), _path(path) {
    _textureId = _graphic.createTexture();
    _graphic.loadTexture(_textureId, path);
  }

  ~TextureComponent() = default;

  uint32_t getTextureId() const { return _textureId; }
  std::string getPath() const { return _path; }


  void update(const std::string& path) {
      _path = path;
      _graphic.loadTexture(_textureId, path);
  }

  std::pair<float, float> getTextureSize()
  {
    return _graphic.getTextureSize(_textureId);
  }

private:
  uint32_t _textureId;
  IGraphic& _graphic;
  std::string _path;
};
}
