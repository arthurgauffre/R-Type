/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HitBoxComponent
*/

#pragma once

#include "AComponent.hpp"

namespace component
{
    class HitBoxComponent : public AComponent
    {
    public:
        HitBoxComponent(uint32_t entityID, float width, float height)
            : AComponent(entityID), _width(width), _height(height) {};
        ~HitBoxComponent() = default;

        float getWidth() const { return _width; }   // Getter for width
        float getHeight() const { return _height; } // Getter for height

        void update(float deltaTime) override {}; // Update the component

    private:
        float _width;  // Width of the hitbox
        float _height; // Height of the hitbox
    };
}