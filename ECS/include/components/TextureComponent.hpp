/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TextureComponent
*/

#pragma once

#include "AComponent.hpp"
#include <SFML/Graphics.hpp>

namespace component
{
    class TextureComponent : public AComponent
    {
    public:
        TextureComponent(uint32_t entityID, const std::string &path)
            : AComponent(entityID)
        {
            texture.loadFromFile(path);
        }
        ~TextureComponent() = default;

        sf::Texture &getTexture() { return texture; } // Get texture

        void update(float deltaTime) override; // Update the component

    private:
        sf::Texture texture; // Texture
    };
}
