/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SpriteComponent
*/

#pragma once

#include "AComponent.hpp"
#include <SFML/Graphics.hpp>

namespace component
{
    class SpriteComponent : public AComponent
    {
    public:
        SpriteComponent(uint32_t entityID, float x, float y)
            : AComponent(entityID), x(x), y(y) {};
        ~SpriteComponent() = default;

        float getX() const { return x; }           // Get x position
        float getY() const { return y; }           // Get y position
        sf::Sprite &getSprite() { return sprite; } // Get sprite

        void update(float deltaTime) override; // Update the component

    private:
        float x;           // x position
        float y;           // y position
        sf::Sprite sprite; // Sprite
    };
}