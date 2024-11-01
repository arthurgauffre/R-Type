/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TextureComponent
*/

#include <components/TextureComponent.hpp>

void component::TextureComponent::update(std::string &path, std::shared_ptr<IGraphic> graphic) {
  _textureId = graphic->createTexture(path);
}