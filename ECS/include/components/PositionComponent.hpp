/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PositionComponent
*/

#pragma once

#include "AComponent.hpp"

namespace component
{
    class PositionComponent : public AComponent
    {
    public:
        PositionComponent(uint32_t entityID, float x, float y)
            : AComponent(entityID), x(x), y(y) {};
        ~PositionComponent() = default;

        float getX() const { return x; } // Return the x position
        float getY() const { return y; } // Return the y position

        void update(float deltaTime) override {}; // Update the component

    private:
        float x; // x position
        float y; // y position
    };
}