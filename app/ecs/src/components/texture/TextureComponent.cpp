/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TextureComponent
*/

#include <components/TextureComponent.hpp>

/**
 * @brief Updates the texture component with a new texture.
 *
 * This function updates the texture component by creating a new texture
 * using the provided path and graphic interface. The texture ID is updated
 * with the ID of the newly created texture.
 *
 * @param path The file path to the texture image.
 * @param graphic A shared pointer to the graphic interface used to create the texture.
 */
void component::TextureComponent::update(std::string &path, std::shared_ptr<IGraphic> graphic) {
  _textureId = graphic->createTexture(path);
}