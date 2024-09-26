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
            : AComponent(entityID), _x(x), _y(y) {};
        ~SpriteComponent() = default;

        float getX() const { return _x; }           // Get x position
        float getY() const { return _y; }           // Get y position
        sf::Sprite &getSprite() { return _sprite; } // Get sprite

        void update(float deltaTime) override; // Update the component

    private:
        float _x;           // x position
        float _y;           // y position
        sf::Sprite _sprite; // Sprite
    };
}