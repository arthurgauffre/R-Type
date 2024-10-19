/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TextureComponent
*/

#include <components/TextureComponent.hpp>

void component::TextureComponent::update(std::string &path) {
    _texture.loadFromFile(path);
  // Update the component
}